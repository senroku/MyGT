#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include "GameObject.h"
#include "SeanManager.h"
//#include "GameObjectAllocator.h"

//Sean��1�t���[���Ɉ��݂̂̌Ăяo��.
//Variant�^�ŌĂяo���Ă��덷���x(Sean�̐��������܂ő����Ȃ�����).
//������̓��\�[�X�߂肷���ł́H
struct Sean
{
	Sean(std::pmr::memory_resource* gallocator) 
	{
		m_resouse = gallocator;
	};
	virtual ~Sean() {}

public:
	template<class T>
	GameObject* createGameObject() {

	}
	virtual void start() = 0;
	virtual void update() = 0;
protected:

protected:
	std::pmr::memory_resource* m_resouse;
};


//###########################################################
//###########################################################
//########               �� OLD                    ##########
//###########################################################
//###########################################################


//�ȉ��͎v�l�j����������.C++�𗝉������Ƃ��Ɏg���c�c�̂��H.
struct Sean2
{
	//���̂܂܂�����g�����Ƃ͋֎~����Ă���.
	Sean2() {
		objects = std::pmr::vector<GameObject>(0);
	}
	~Sean2() {}

	template<std::size_t N>
	Sean2(std::pmr::memory_resource* gallocator) {
		//���Ԃ�Ado_allocate�̏�����Vector���ŏ���ɂ���Ă����
		objects = std::pmr::vector<GameObject>(N, gallocator);
	}
public:
	//����H
	std::string name = "Sean";
	//UINT16 id = 0;
	//vtable��Cast�Ŏg�p�\��.
	//enemy�Ƃ�player�Ƃ���GameObject�Q�𕡐�������
	//Sean���Ƃɕς��.
	//std::pmr::vector<std::unique_ptr<GameObject>> objects;

public:
	template<class T>
	GameObject* createGameObject()
	{
		static_assert(std::is_base_of_v<GameObject, T>, "T is not extended interface class");
		objects.push_back(new T());
		return objects.back;
	}

	virtual void start() {}
	//1�t���[���Ɉ��݂̂̌Ăяo���̂���vtable�l���s�v.
	//���������������Ȃ���΂Ȃ�Ȃ��Ƃ���objects�𕪂��āA
	//update�ł��������ɍ����������Ă�������.
	virtual void update() {
		return;
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i].update();
		}
	}
private:
	std::pmr::vector<GameObject> objects;
	//	std::pmr::memory_resource* resourse;
};

