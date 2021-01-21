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
		virtual void onLoad(const std::string& path);//Virtual function onLoad allows for loading assets of different data types 

		std::string getPath(); //Used to get the file path of an asset
		std::shared_ptr<Core> getCore();

	private:
		friend struct myengine::AssetManager;

		std::string path; //Stores the path of an asset
		std::weak_ptr<Core> core;

	};

}

#endif
