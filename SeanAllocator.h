#pragma once
#include <iostream>
#include <memory_resource>
#include <cstddef>
#include <vector>

//�X�^�b�N�̈悩�烁���������蓖�Ă�memory_resource����]
//�T�C�Y���ł������A���C�����g�s���̃V�[���̃��\�[�X�������ŊǗ�.
//���̂��߁AGameObject�̊Ǘ�����������͂����ƂɂȂ�.
//Policy�x�[�X�̃������A���P�[�^�ł��悩��������������o���邱�Ƃɂ���.

namespace MyGT {

    template<std::size_t N>
    struct stack_resource : public std::pmr::memory_resource {

        stack_resource() = default;
        //�R�s�[�ɈӖ����Ȃ��̂ŋ֎~
        stack_resource(const stack_resource&) = delete;
        stack_resource& operator=(const stack_resource&) = delete;

        void* do_allocate(std::size_t bytes, [[maybe_unused]] std::size_t alignment) override {
            //�󂫂��Ȃ�
            if (N <= m_index) throw std::bad_alloc{};

            //////2�̗ݏ���`�F�b�N�iAVX512�̃A���C�����g�v���ł���64byte���ő�Ƃ��Ă����j
            ////���̂͌��̂�A�����Sean��GameObjectSize���K�v�ɂȂ邽�߂���̃T�C�Y.
            //bool is_pow2 = false;
            //for (std::size_t pow2 = 1; pow2 <= std::size_t(N); pow2 *= 2) {
            //    if (alignment >= pow2) {
            //        is_pow2 = true;
            //        break;
            //    } 
            //}

            ////2�̗ݏ�łȂ��A���C�����g�v����alignof(std::max_align_t)��
            //if (!is_pow2) {
            //    alignment = alignof(std::max_align_t);
            //}

            auto addr = reinterpret_cast<std::uintptr_t>(&m_buffer[m_index]);

            ////�A���C�����g�v���ɍ��킹��
            //while ((addr & std::uintptr_t(alignment - 1)) != 0) {
            //    ++addr;
            //    ++m_index;
            //}

            m_index += bytes;

            //�T�C�Y������Ȃ��Ȃ�����
            if (N <= m_index) throw std::bad_alloc{};

            return reinterpret_cast<void*>(addr);
        }

        void do_deallocate(void* p, std::size_t bytes, [[maybe_unused]] std::size_t alignment) override {
            auto addr = static_cast<std::byte*>(p);
            auto end = std::end(m_buffer);

            if (m_buffer <= addr && addr < end) {
                //���Ă��̈���[�����߂��邾��
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