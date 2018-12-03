#include "shipwreck.hh"

namespace Student {

Shipwreck::Shipwreck(int typeId):Common::Actor(typeId){

}

std::string Shipwreck::getActorType() const
{
    return "shipwreck";
}
}
