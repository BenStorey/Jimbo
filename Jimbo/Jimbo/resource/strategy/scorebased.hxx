#ifndef JIMBO_RESOURCE_STRATEGY_SCOREBASED_HXX
#define JIMBO_RESOURCE_STRATEGY_SCOREBASED_HXX

/////////////////////////////////////////////////////////
// scorebased.hxx
//
// Ben Storey
//
// This strategy gives points to resources based on things like their size, the time they were loaded,
// priority as set by the user (if we want), how often resources are accessed, how many dependencies etc
//
/////////////////////////////////////////////////////////

#include "resource/resourceloadstrategy.hxx"

namespace jimbo
{
    class ScoreBasedCache : public ResourceLoadStrategy
    {
        
    };
}


#endif // JIMBO_RESOURCE_STRATEGY_SCOREBASED_HXX