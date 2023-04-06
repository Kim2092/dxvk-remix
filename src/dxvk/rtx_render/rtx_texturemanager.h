/*
* Copyright (c) 2022-2023, NVIDIA CORPORATION. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <mutex>
#include <queue>

#include "../../util/thread.h"
#include "../../util/rc/util_rc_ptr.h"
#include "../../util/sync/sync_signal.h"
#include "rtx_texture.h"

namespace dxvk {
  class DxvkDevice;
  class DxvkContext;
  struct ManagedTexture;

  class RtxTextureManager {
  public:
    RtxTextureManager(const Rc<DxvkDevice>& device);
    ~RtxTextureManager();

    void start();
    Rc<ManagedTexture> preloadTexture(const Rc<AssetData>& assetData, ColorSpace colorSpace,
      const Rc<DxvkContext>& context, bool forceLoad);
    void scheduleTextureUpload(TextureRef& texture, Rc<DxvkContext>& immediateContext, bool allowAsync);
    void unloadTexture(const Rc<ManagedTexture>& texture);
    void releaseTexture(const Rc<ManagedTexture>& texture);
    void synchronize(bool dropRequests = false);
    void kickoff();

    void demoteTexturesFromVidmem();
    uint32_t updateMipMapSkipLevel(const Rc<DxvkContext>& context);

    static int calcPreloadMips(int mipLevels);

    inline static XXH64_hash_t getUniqueKey() {
      static uint64_t ID;
      XXH64_hash_t key;

      do {
#ifdef _DEBUG
        assert(ID + 1 > ID && "Texture hash key id rollover detected!");
#endif
        ++ID;
        key = XXH3_64bits(&ID, sizeof(ID));
      } while (key == kInvalidTextureKey);

      return key;
    }

  private:
    Rc<DxvkDevice> m_device;
    Rc<DxvkContext> m_ctx;
    dxvk::mutex m_queueMutex;
    std::atomic<bool> m_stopped = { false };
    std::atomic<bool> m_dropRequests = false;
    dxvk::condition_variable m_condOnAdd;
    dxvk::condition_variable m_condOnSync;
    bool m_kickoff = false;
    std::queue<Rc<ManagedTexture>> m_textureQueue;
    std::atomic<uint32_t> m_texturesPending = { 0u };
    dxvk::thread m_thread;

    uint32_t m_minimumMipLevel;
    fast_unordered_cache<Rc<ManagedTexture>> m_textures;

    void threadFunc();
    void uploadTexture(const Rc<ManagedTexture>& texture);
  };

} // namespace dxvk
