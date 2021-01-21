#ifndef MYENGINE_ASSET_H
#define MYENGINE_ASSET_H

#include <string>
#include <memory>

namespace myengine
{

	struct Core;
	struct AssetManager;

	struct Asset
	{
		virtual ~Asset();
		virtual void onLoad(const std::string& path);

		std::string getPath();
		std::shared_ptr<Core> getCore();

	private:
		friend struct myengine::AssetManager;

		std::string path;
		std::weak_ptr<Core> core;

	};

}

#endif
