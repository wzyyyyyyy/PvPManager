#pragma once
#include <string>

namespace PM {
	void initDB();
	std::string getLanguage();
	void loadLanguage();
	void initPvPArea();
	void setPvPAreaOfDim0(AABB area);
	void setPvPAreaOfDim1(AABB area);
	void setPvPAreaOfDim2(AABB area);
}