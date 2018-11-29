#ifndef SHIPWRECK_HH
#define SHIPWRECK_HH

#include "actor.hh"
#include <string>

namespace Student {


class Shipwreck : public Common::Actor
{
public:
    Shipwreck(int typeId);

    virtual std::string getActorType() const;

};
}
#endif // SHIPWRECK_HH
