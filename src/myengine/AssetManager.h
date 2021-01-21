#ifndef MYENGINE_ASSETMANAGER_H
#define MYENGINE_ASSETMANAGER_H
#include "Asset.h"

#include <vector>
#include <memory>
#include <string>

namespace myengine
{
    struct Core;
    struct AssetManager
    {
        template <typename T>
        std::shared_ptr<T> load(const std::string& path)
        {
            std::shared_ptr<T> rtn;

            for (size_t i = 0; i < assets.size(); i++)
            {
                if (path == assets.at(i)->getPath())
                {
                    rtn = std::dynamic_pointer_cast<T>(assets.at(i));
                    if (!rtn) continue;

                    return rtn;
                }
            }

            rtn = std::make_shared<T>();
            rtn->core = core;
            rtn->path = path;
            rtn->onLoad();
            assets.push_back(rtn);

            return rtn;
        }

    private:
        friend struct myengine::Core;

        std::vector<std::shared_ptr<Asset>> assets;
        std::weak_ptr<Core> core;
    };

}

#endif
