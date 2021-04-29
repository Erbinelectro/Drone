#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

#include<math.h>

/**
* �N�H�[�^�j�I���̑����C�����C�|���Z�Ȃǂ��ȒP�ɂł���悤�ɂȂ�܂��D
* @author  Gaku MATSUMOTO
* @bref  �N�H�[�^�j�I�����g����N���X�ł��D
*/
class Quaternion {
public:
	/**
		@bref	Quaternion�C���X�^���X�𐶐����܂�
	*/
	Quaternion() {
		w = 1.0f;
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};
	/**
		@bref	�v�f�������Ȃ���C�C���X�^���X�𐶐����܂��D
		@param[in]  _w  ����w�̏����l
		@param[in]  _x  ����i�̏����l
		@param[in]  _y  ����j�̏����l
		@param[in]  _z  ����k�̏����l
	*/
	Quaternion(double _w, double _x, double _y, double _z) {
		w = _w; x = _x; y = _y; z = _z;
	};

public:
	double w;
	double x;
	double y;
	double z;

public:

	/**
		@bref  �N�H�[�^�j�I���̗v�f���R�s�[���܂��D
		@note  �ʏ�̐��̂悤�ɑ���ł��܂�
	*/
	Quaternion operator=(Quaternion r) {
		w = r.w;
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	};

	/**
		@bref  �N�H�[�^�j�I���𑫂��đ�����܂��D
		@note  �ʏ�̐��̂悤�ɑ���ł��܂�
	*/
	Quaternion operator+=(Quaternion r) {
		w += r.w;
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	};

	/**
		@bref  �N�H�[�^�j�I���������đ�����܂��D
		@note  �ʏ�̐��̂悤�ɑ���ł��܂�
	*/
	Quaternion operator-=(Quaternion r) {
		w -= r.w;
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	};

	/**
	*	@bref	�N�H�[�^�j�I���̊|���Z�����܂��D
	*	@note	���̍ۂ������͏d�v�ł��D
	*/
	Quaternion operator*=(Quaternion r) {
		static Quaternion QQ;
		QQ.w = w * r.x - x * r.x - y * r.y - z * r.z;
		QQ.x = x * r.w + w * r.x - z * r.y + y * r.z;
		QQ.y = y * r.w + z * r.x + w * r.y - x * r.z;
		QQ.z = z * r.w - y * r.x + x * r.y + w * r.z;
		w = QQ.w;
		x = QQ.x;
		y = QQ.y;
		z = QQ.z;
		return *this;
	};

	/**
		@bref	�N�H�[�^�j�I���̕��f������Ԃ��܂��D
		@note	�{���̓A�X�^���X�N���ǂ������̂ł����C�|�C���^�ƕ���킵���̂Ń}�C�i�X�ɂ��܂����D
	*/
	Quaternion operator-() {
		Quaternion Q;
		Q.w = w;
		Q.x = -x;
		Q.y = -y;
		Q.z = -z;
		return Q;
	};

	/**
		@bref	�N�H�[�^�j�I���𐳋K�����āC�P�ʃN�H�[�^�j�I���ɂ��܂��D
		@note	�|���Z�Ȃǂ��s�����тɎ��s���邱�Ƃ������߂��܂��D
	*/
	void normalize() {
		double norm = sqrt(w * w + x * x + y * y + z * z);
		if (norm != 0.0) {
			w /= norm;
			x /= norm;
			y /= norm;
			z /= norm;
			return;
		}
		else {
			return;
		}
	};
};

/**
* @fn Quaternion operator*(Quaternion l, Quaternion r)
* @bref �N�H�[�^�j�I���̊|���Z�����܂��D���̍ہC�������d�v�ł��D
*/
Quaternion operator*(Quaternion l, Quaternion r) {
	static Quaternion Q;
	Q.w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
	Q.x = l.x * r.w + l.w * r.x - l.z * r.y + l.y * r.z;
	Q.y = l.y * r.w + l.z * r.x + l.w * r.y - l.x * r.z;
	Q.z = l.z * r.w - l.y * r.x + l.x * r.y + l.w * r.z;
	/*double q0Dot, q1Dot, q2Dot, q3Dot;//�N�H�[�^�j�I���̎��Ԕ���
	q0Dot =        -gx*qg1 - gy*qg2 - gz*qg3;
	q1Dot = gx*qg0         + gz*qg2 - gy*qg3;
	q2Dot = gy*qg0 - gz*qg1         + gx*qg3;
	q3Dot = gz*qg0 + gy*qg1 - gx*qg2;*/
	return Q;
};

/**
* @fn Quaternion operator*(double s, Quaternion q)
* @bref �N�H�[�^�j�I�����X�J���[�{���܂��D�D
*/
Quaternion operator*(double s, Quaternion q) {
	static Quaternion Q;
	Q.w = q.w * s;
	Q.x = q.x * s;
	Q.y = q.y * s;
	Q.z = q.z * s;
	return Q;
};

/**
* @fn Quaternion operator*(Quaternion q, double s)
* @bref �N�H�[�^�j�I�����X�J���[�{���܂��D�D
*/
Quaternion operator*(Quaternion q, double s) {
	static Quaternion Q;
	Q.w = q.w * s;
	Q.x = q.x * s;
	Q.y = q.y * s;
	Q.z = q.z * s;
	return Q;
};

/**
* @fn Quaternion operator+(Quaternion l, Quaternion r)
* @bref �N�H�[�^�j�I���̑����Z�����܂��D
*/
Quaternion operator+(Quaternion l, Quaternion r) {
	static Quaternion Q;
	Q.w = l.w + r.w;
	Q.x = l.x + r.x;
	Q.y = l.y + r.y;
	Q.z = l.z + r.z;
	return Q;
}

/**
* @fn Quaternion operator-(Quaternion l, Quaternion r)
* @bref �N�H�[�^�j�I���̈����Z�����܂��D
*/
Quaternion operator-(Quaternion l, Quaternion r) {
	static Quaternion Q;
	Q.w = l.w - r.w;
	Q.x = l.x - r.x;
	Q.y = l.y - r.y;
	Q.z = l.z - r.z;
	return Q;
}

#endif