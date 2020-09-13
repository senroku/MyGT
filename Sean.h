#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SeanManager.h"
//#include "GameObjectAllocator.h"

//Sean��1�t���[���Ɉ��݂̂̌Ăяo��.
namespace MyGT {
	//struct SeanInterface {
	//	virtual void start() = 0;
	//	virtual void update() = 0;
	//};
	//template<std::size_t N>
	struct Sean 
	{
		Sean(std::pmr::memory_resource* gallocator)
		{
			m_resouse = gallocator;
		};
		virtual ~Sean() {}

	public:
		template<typename T>
		void addManager(T* gom){
			static_assert(std::is_base_of_v<GameOvjectManagerInrterface, T>, "T is not GameObjectManager extended interface class");
		}
		template<typename T>
		GameObject* createGameObject() {}
		virtual void start() = 0;
		virtual void update() = 0;
	protected:
		//�s�v�ȏꍇ������̂�.
		//�t���[���̍Ō�ɔj���쐬����ꍇ�͎g���ׂ�.
		virtual void objectDeleateCreate() {};

	protected:
		std::pmr::memory_resource* m_resouse;
	};

}
