#pragma once

#include "Component.h"
#include "DxLib.h"
#include <map>


namespace MyGT {

	namespace SRC{
		constexpr int id_max = 1000;

		const constexpr char* test_char = "";


		//�x��
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
			//id�Ǘ�,<id,�g�p��>.
			static std::pair<int, int> ids[id_max];

		private:
			int id;
		};
	}

	// ������@�p.
	struct Sprite {
		SRC::Sprite* spritePoint;
	};

}
