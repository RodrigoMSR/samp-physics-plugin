#define _USE_MATH_DEFINES

#include <cmath>
#include <sampgdk.h>

namespace Util
{
	double sin_degrees(double degrees)
	{
		return sin(degrees * (M_PI / 180.0));
	}

	double cos_degrees(double degrees)
	{
		return cos(degrees * (M_PI / 180.0));
	}

	double atan2_degrees(double y, double x)
	{
		return atan2(y, x) * (180.0 / M_PI);
	}

	double asin_degrees(double x)
	{
		return asin(x) * (180.0 / M_PI);
	}

	float vectordotp(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z)
	{
		return (v1x * v2x + v1y * v2y + v1z * v2z);
	}

	void projectVonU(float vx, float vy, float vz, float ux, float uy, float uz, float& x, float& y, float& z)
	{
		float fac = vectordotp(vx, vy, vz, ux, uy, uz) / vectordotp(ux, uy, uz, ux, uy, uz);
		x = ux * fac;
		y = uy * fac;
		z = uz * fac;
	}

	bool check_segment_intersection(float x1, float y1, float x2, float y2, float xc, float yc, float r, float& x, float& y)
	{
		float v1[2];
		float v2[2];
		v1[0] = x2 - x1;
		v1[1] = y2 - y1;
		v2[0] = xc - x1;
		v2[1] = yc - y1;
		float v1_len = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
		v1[0] /= v1_len;
		v1[1] /= v1_len;
		float proj = vectordotp(v2[0], v2[1], 0.0, v1[0], v1[1], 0.0);
		x = proj * v1[0] + x1;
		y = proj * v1[1] + y1;
		return ((proj < v1_len + r && proj > 0 - r) && ((x - xc) * (x - xc) + (y - yc) * (y - yc) < (r * r)));
	}

	void vectorcrossp(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float& c1, float& c2, float& c3)
	{
		c1 = (v1y * v2z) - (v1z * v2y),
		c2 = (v1z * v2x) - (v1x * v2z),
		c3 = (v1x * v2y) - (v1y * v2x);
	}

	void quatNormalize(float& q_w, float& q_x, float& q_y, float& q_z)
	{
		float magnitude = sqrt(q_w*q_w + q_x*q_x + q_y*q_y + q_z*q_z);

		if (magnitude == 0.0)
		{
			q_w = 1.0;
			q_x = 0.0;
			q_y = 0.0;
			q_z = 0.0;
		}
		else
		{
			q_w /= magnitude;
			q_x /= magnitude;
			q_y /= magnitude;
			q_z /= magnitude;
		}
	}

	void quatFromAxisAngle(float x, float y, float z, float angle, float& q_w, float& q_x, float& q_y, float& q_z)
	{
		float omega, s;

		s = sqrt(x*x + y*y + z*z);

		if (s > 0.01)
		{
			x /= s;
			y /= s;
			z /= s;

			omega = 0.5 * angle;
			s = sin_degrees(omega);

			q_x = s*x;
			q_y = s*y;
			q_z = s*z;
			q_w = cos_degrees(omega);
		}
		else
		{
			q_x = 0.0;
			q_y = 0.0;
			q_z = 0.0;
			q_w = 1.0;
		}

		quatNormalize(q_w, q_x, q_y, q_z);
	}


	/* The following are from i_quat.inc, made by IllidanS4 (spacemud)
	https://github.com/IllidanS4/i_quat/blob/master/i_quat.inc */

	float asin_limit(float value)
	{
		if(value > 1.0) value = 1.0;
		else if(value < -1.0) value = -1.0;
		return asin_degrees(value);
	}

	float atan2_limit(float x, float y)
	{
		if(x > 1.0) x = 1.0;
		else if(x < -1.0) x = -1.0;
		if(y > 1.0) y = 1.0;
		else if(y < -1.0) y = -1.0;
		return atan2_degrees(x, y);
	}

	void getQuatProduct(const float q1[4], const float q2[4], float q3[4])
	{
		float w = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
		float x = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
		float y = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
		float z = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
		q3[0] = w, q3[1] = x, q3[2] = y, q3[3] = z;
	}

	void getQuaternionAngles(float w, float x, float y, float z, float& xa, float& ya, float& za)
	{
		#if defined QUAT_FLOAT_EPSILON
		static const float epsilon = QUAT_FLOAT_EPSILON;
		#else
		static const float epsilon = 0.00000202655792236328125;
		#endif

		float temp = 2*y*z - 2*x*w;

		if(temp >= 1-epsilon)
		{
			xa = 90.0;
			ya = -atan2_limit(y, w);
			za = -atan2_limit(z, w);
		}else if(-temp >= 1-epsilon)
		{
			xa = -90.0;
			ya = -atan2_limit(y, w);
			za = -atan2_limit(z, w);
		}else{
			xa = asin_limit(temp);
			ya = -atan2_limit(x*z + y*w, 0.5 - x*x - y*y);
			za = -atan2_limit(x*y + z*w, 0.5 - x*x - z*z);
		}
	}

	void getRotationQuaternion(float x, float y, float z, float& qw, float& qx, float& qy, float& qz)
	{
		float cx = cos_degrees(-0.5*x);
		float sx = sin_degrees(-0.5*x);
		float cy = cos_degrees(-0.5*y);
		float sy = sin_degrees(-0.5*y);
		float cz = cos_degrees(-0.5*z);
		float sz = sin_degrees(-0.5*z);
		qw = cx * cy * cz + sx * sy * sz;
		qx = cx * sy * sz + sx * cy * cz;
		qy = cx * sy * cz - sx * cy * sz;
		qz = cx * cy * sz - sx * sy * cz;
	}

	void storeFloatInNative(AMX *amx, cell output, float value)
	{
		cell *address;
		amx_GetAddr(amx, output, &address);
		*address = amx_ftoc(value);
	}

	void storeIntegerInNative(AMX *amx, cell output, int value)
	{
		cell *address;
		amx_GetAddr(amx, output, &address);
		*address = value;
	}
}