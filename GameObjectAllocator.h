#pragma once

//https://cpprefjp.github.io/reference/memory_resource/memory_resource.html
//読み込みを早くするため作成.
//特にメニュー等の高速化を期待.
//ほかの方法としてはメニューはシーン分けしない等.


#include <memory_resource>
#include <array>
#include <vector>
#include <cassert>
#include <cstddef>
#include <iostream>


//Vector<GameObject>で使用される前提のメモリリソース.
//消された場所へGameObjectをコピーする.
//最初に指定されたサイズのアライメントでメモリを渡していく.
//updateの最後に削除→追加の順で行う前提のメモリリソース.

//削除＝空き番号追加

//1:26 2020/06/30a　Vectorで使うとその先のメモリ確保できなくない？

//Seanが持っているデータ領域を利用する前提があってのこれ.

//こいつをAllocatorのAllocateで入れること


//そもそもSeanAllocaterにVectorでとればいいから要らないのでは？
namespace MyGT {
    template<std::size_t N>
    struct GameObjectAllocator : public std::pmr::memory_resource {

        GameObjectAllocator() = default;
        //コピーに意味がないので禁止
        GameObjectAllocator(const GameObjectAllocator&) = delete;
        GameObjectAllocator& operator=(const GameObjectAllocator&) = delete;

        void* do_allocate(std::size_t bytes, std::size_t alignment) override {
            //空きがない
            if (N <= m_index) throw std::bad_alloc{};

            ////なぜ必要？64bitなら8byteで定義しとけばいいような気が(知識不足でよくわかってない).
            ////2の累乗をチェック（AVX512のアライメント要求である64byteを最大としておく）
            //bool is_pow2 = false;
            //for (std::size_t pow2 = 1; pow2 <= std::size_t(64); pow2 *= 2) {
            //    if (alignment == pow2) {
            //        is_pow2 = true;
            //        break;
            //    }
            //}

            ////2の累乗でないアライメント要求はalignof(std::max_align_t)へ
            //if (!is_pow2) {
            //    alignment = alignof(std::max_align_t);
            //}

            auto addr = reinterpret_cast<std::uintptr_t>(&m_buffer[m_index]);

            ////アライメント要求に合わせる
            //while ((addr & std::uintptr_t(alignment - 1)) != 0) {
            //    ++addr;
            //    ++m_index;
            //}

            m_index += bytes;

            //サイズが足りなくなったら
            if (N <= m_index) throw std::bad_alloc{};
            //m_firstIndex = new (1024);
            return reinterpret_cast<void*>(addr);
        }

        void do_deallocate(void* p, [[maybe_unused]] std::size_t bytes, [[maybe_unused]] std::size_t alignment) override {


        }

        bool do_is_equal(const memory_resource& other) const noexcept override {
            return this == &other;
        }
    public:
        size_t size;

    private:
        std::size_t m_index{};
        void* m_firstIndex;
    };
}