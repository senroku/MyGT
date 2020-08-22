#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include "GameObject.h"
#include "SeanManager.h"
//#include "GameObjectAllocator.h"

//Seanは1フレームに一回のみの呼び出し.
//Variant型で呼び出しても誤差程度(Seanの数もそこまで多くないため).
//↑それはリソース捕りすぎでは？
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
//########               ↓ OLD                    ##########
//###########################################################
//###########################################################


//以下は思考破棄したもの.C++を理解したときに使う……のか？.
struct Sean2
{
	//そのままこれを使うことは禁止されている.
	Sean2() {
		objects = std::pmr::vector<GameObject>(0);
	}
	~Sean2() {}

	template<std::size_t N>
	Sean2(std::pmr::memory_resource* gallocator) {
		//たぶん、do_allocateの処理をVector内で勝手にやってくれる
		objects = std::pmr::vector<GameObject>(N, gallocator);
	}
public:
	//いる？
	std::string name = "Sean";
	//UINT16 id = 0;
	//vtableはCastで使用予定.
	//enemyとかplayerとかでGameObject群を複数持つため
	//Seanごとに変わる.
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
	//1フレームに一回のみの呼び出しのためvtable考慮不要.
	//処理を効率化しなければならないときはobjectsを分けて、
	//updateでいい感じに高速化させてください.
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

