#include "pch.h"
#include "Transform.h"
#include <fstream>
#include <string>

namespace nc
{
	std::istream& nc::operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;

		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);

		

		std::getline(stream, line);
		transform.angle = stof(line);


		return stream;
	}

	void Transform::update()
	{
		nc::Matrix33 mxs;
		mxs.Scale(scale);

		nc::Matrix33 mxr;
		mxr.Rotate(angle);

		nc::Matrix33 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt;
	}

	void Transform::update(const Matrix33& mx)
	{
		nc::Matrix33 mxs;
		mxs.Scale(scale);

		nc::Matrix33 mxr;
		mxr.Rotate(angle);

		nc::Matrix33 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt * mx;
	}

}
