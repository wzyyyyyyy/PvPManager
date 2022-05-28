#pragma once
#include <string>

namespace PM {
	void initDB();
	void loadConf();
	std::string getLanguage();
	void loadLanguage();
	void initPvPArea();
	int getCoolDownTime();
	void setPvPAreaOfDim0(AABB area);
	void setPvPAreaOfDim1(AABB area);
	void setPvPAreaOfDim2(AABB area);
}