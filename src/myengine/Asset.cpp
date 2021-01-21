#include "Asset.h"

namespace myengine
{

	Asset::~Asset() { }
	void Asset::onLoad(const std::string& path) { }

	std::string Asset::getPath()
	{
		return path;
	}

	std::shared_ptr<Core> Asset::getCore()
	{
		return core.lock();
	}

}

