#pragma once
#include <iostream>
#include <memory_resource>
#include <cstddef>
#include <vector>

//スタック領域からメモリを割り当てるmemory_resource実装]
//サイズがでかいかつアライメント不明のシーンのリソースをここで管理.
//そのため、GameObjectの管理もここからはくことになる.
//Policyベースのメモリアロケータでもよかったがこちらを覚えることにした.

namespace MyGT {

    template<std::size_t N>
    struct stack_resource : public std::pmr::memory_resource {

        stack_resource() = default;
        //コピーに意味がないので禁止
        stack_resource(const stack_resource&) = delete;
        stack_resource& operator=(const stack_resource&) = delete;

        void* do_allocate(std::size_t bytes, [[maybe_unused]] std::size_t alignment) override {
            //空きがない
            if (N <= m_index) throw std::bad_alloc{};

            //////2の累乗をチェック（AVX512のアライメント要求である64byteを最大としておく）
            ////↑のは元のやつ、今回はSeanのGameObjectSizeが必要になるためそれのサイズ.
            //bool is_pow2 = false;
            //for (std::size_t pow2 = 1; pow2 <= std::size_t(N); pow2 *= 2) {
            //    if (alignment >= pow2) {
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

            return reinterpret_cast<void*>(addr);
        }

        void do_deallocate(void* p, std::size_t bytes, [[maybe_unused]] std::size_t alignment) override {
            auto addr = static_cast<std::byte*>(p);
            auto end = std::end(m_buffer);

            if (m_buffer <= addr && addr < end) {
                //当てた領域をゼロ埋めするだけ
                for (std::size_t i = 0; i < bytes; ++i) {
                    if ((addr + i) < end) {
                        addr[i] = std::byte(0);
                    }
                }
            }
            m_index -= bytes;
        }

        bool do_is_equal(const memory_resource& other) const noexcept override {
            return this == &other;
        }

    private:
    public:
        std::byte m_buffer[N]{};
        std::size_t m_index{};
    };

}