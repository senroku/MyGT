#pragma once

//https://cpprefjp.github.io/reference/memory_resource/memory_resource.html
//�ǂݍ��݂𑁂����邽�ߍ쐬.
//���Ƀ��j���[���̍�����������.
//�ق��̕��@�Ƃ��Ă̓��j���[�̓V�[���������Ȃ���.


#include <memory_resource>
#include <array>
#include <vector>
#include <cassert>
#include <cstddef>
#include <iostream>


//Vector<GameObject>�Ŏg�p�����O��̃��������\�[�X.
//�����ꂽ�ꏊ��GameObject���R�s�[����.
//�ŏ��Ɏw�肳�ꂽ�T�C�Y�̃A���C�����g�Ń�������n���Ă���.
//update�̍Ō�ɍ폜���ǉ��̏��ōs���O��̃��������\�[�X.

//�폜���󂫔ԍ��ǉ�

//1:26 2020/06/30a�@Vector�Ŏg���Ƃ��̐�̃������m�ۂł��Ȃ��Ȃ��H

//Sean�������Ă���f�[�^�̈�𗘗p����O�񂪂����Ă̂���.

//������Allocator��Allocate�œ���邱��


//��������SeanAllocater��Vector�łƂ�΂�������v��Ȃ��̂ł́H
namespace MyGT {
    template<std::size_t N>
    struct GameObjectAllocator : public std::pmr::memory_resource {

        GameObjectAllocator() = default;
        //�R�s�[�ɈӖ����Ȃ��̂ŋ֎~
        GameObjectAllocator(const GameObjectAllocator&) = delete;
        GameObjectAllocator& operator=(const GameObjectAllocator&) = delete;

        void* do_allocate(std::size_t bytes, std::size_t alignment) override {
            //�󂫂��Ȃ�
            if (N <= m_index) throw std::bad_alloc{};

            ////�Ȃ��K�v�H64bit�Ȃ�8byte�Œ�`���Ƃ��΂����悤�ȋC��(�m���s���ł悭�킩���ĂȂ�).
            ////2�̗ݏ���`�F�b�N�iAVX512�̃A���C�����g�v���ł���64byte���ő�Ƃ��Ă����j
            //bool is_pow2 = false;
            //for (std::size_t pow2 = 1; pow2 <= std::size_t(64); pow2 *= 2) {
            //    if (alignment == pow2) {
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