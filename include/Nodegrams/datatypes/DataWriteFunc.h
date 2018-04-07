
#pragma once
#ifndef NDGM_DT_DATAWRITEFUNC_H
#define NDGM_DT_DATAWRITEFUNC_H

namespace Nodegrams
{

class DataBox;
typedef void (*DataWriteFunc)(DataBox*, DataBox*);

} // namespace Nodegrams
#endif // ifndef NDGM_DT_DATAWRITEFUNC_H
