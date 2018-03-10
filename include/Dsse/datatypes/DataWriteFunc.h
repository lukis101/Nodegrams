
#pragma once
#ifndef DSSE_DT_DATAWRITEFUNC_H
#define DSSE_DT_DATAWRITEFUNC_H

namespace dsse
{

class DataBox;
typedef void (*DataWriteFunc)(DataBox*, DataBox*);

}
#endif // ifndef DSSE_DT_DATAWRITEFUNC_H
