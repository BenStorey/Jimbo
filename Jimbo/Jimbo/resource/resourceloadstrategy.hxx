#ifndef JIMBO_RESOURCE_RESOURCELOADSTRATEGY_HXX
#define JIMBO_RESOURCE_RESOURCELOADSTRATEGY_HXX

/////////////////////////////////////////////////////////
// resourceloadstrategy.hxx
//
// Ben Storey
//
// A resource load strategy is a structure that determines when resources
// should be loaded or have their memory released. The ResourceManager class
// itself will do the actual unloading/loading calls, but strategies determine
// when and under what circumstances.
//
/////////////////////////////////////////////////////////

namespace jimbo
{
    class ResourceLoadStrategy
    {
        // Take reference to the ResourceManager so we know from who to request things

        // Should we have hintLoad supported by everyone? I'm tempted to say yes

        // Probably this should be the only visible component to a Scene, they don't
        // need to see the ResourceManager behind it ever
    };
}

#endif // JIMBO_RESOURCE_RESOURCELOADSTRATEGY_HXX