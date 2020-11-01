#pragma once

#include "Component.h"
#include "DxLib.h"
#include <map>


namespace MyGT {

	namespace SRC{
		constexpr int id_max = 1000;

		const constexpr char* test_char = "";


		//遅い
		struct Sprite : public Component{
			using Component::Component;
			Sprite() = default;
			template<char* str>
			Sprite(GameObject* obj) :Component(obj) {
				if constexpr (str == test_char) {
					LoadGraph(str);
				}
			}

		public:
			~Sprite() {}

			void start() {
				//position = &(object->transform.position);
			}
			void update() {
				//			DrawGraph(object->transform.position->x, object->transform.position->y, id, true);
			}

		private:
			//id管理,<id,使用数>.
			static std::pair<int, int> ids[id_max];

		private:
			int id;
		};
	}

	// 所持情法用.
	struct Sprite {
		SRC::Sprite* spritePoint;
	};

}
