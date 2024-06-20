#include <Interface/IEngine.h>


namespace ts
{
    IEngine::IEngine(): estate_(STOP), etrademode_(HISTORY), etradelock_(LOCKED)
    {};

    IEngine::~IEngine(){};

    //other member functions are set to pure virtual function

} // namespace ts
