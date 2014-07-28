#pragma once

#include "EnemyBullet.h"
#include "EnemyBullet01.h"

class EnemyBullet05 : public EnemyBulletUnit{
	class Infomation{
	private:
		std::vector<Vector> position_;
		int bulletNum_;
		float rollSpeed_;
		float radius_; 
		float speed_;
		float angle_;
		bool updated_;
		Counter cnt_;
		
	public:
		Infomation(Vector& position, float speed, float angle, int bulletNum, float  rollSpeed, float radius) :
		speed_(speed),
		angle_(angle),
		bulletNum_(bulletNum),
		rollSpeed_(rollSpeed),
		radius_(radius),
		updated_(false)
		{
			position_.resize(bulletNum_ + 1);
			position_[0] = position;
			calcPosition();
		}

		void update(){
			if(updated_) return;

			const float RAD = angle_ * TWO_PI;

			position_[0].x += cosf(RAD) * speed_;
			position_[0].y += sinf(RAD) * speed_;
			calcPosition();
		}

		Vector getPosition(int n){ return position_[n]; }
		void setUpdated(bool value){ updated_ = value; }
		bool getUpdated_(){ return updated_; }
		int getNum(){ return position_.size() - 1; }

	private:
		void calcPosition(){
			float angle = rollSpeed_ * cnt_++;

			for(int i = 1, size = position_.size(); i < size; ++i){
				const float RAD = static_cast<float>(i) / static_cast<float>(size) * TWO_PI + angle;

				position_[i].x = position_[0].x + cosf(RAD) * radius_;
				position_[i].y = position_[0].y + sinf(RAD) * radius_;
			}
		}
	};

private:
	static Infomation infomation_;
	int number;

public:
	EnemyBullet05(int imageHandle, Vector& position);
	void update();
};

void createEnemyBullet05(int imageHandle, Vector& position, float speed, float angle, int bulletNum, float  rollSpeed, float radius){

}