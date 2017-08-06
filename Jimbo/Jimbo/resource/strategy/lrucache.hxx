#ifndef JIMBO_RESOURCE_STRATEGY_LRUCACHE_HXX
#define JIMBO_RESOURCE_STRATEGY_LRUCACHE_HXX

/////////////////////////////////////////////////////////
// lrucache.hxx
//
// Ben Storey
//
// This strategy will keep the latest used in memory and release
// old resources that haven't been used for some time
//
/////////////////////////////////////////////////////////

#include "resource/resourceloadstrategy.hxx"

namespace jimbo
{
    class LRUCache : public ResourceLoadStrategy
    {

    };
}


#endif // JIMBO_RESOURCE_STRATEGY_LRUCACHE_HXX