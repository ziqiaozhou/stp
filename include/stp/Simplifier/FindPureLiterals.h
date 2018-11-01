/********************************************************************
 * AUTHORS: Trevor Hansen
 *
 * BEGIN DATE: 09/02/2011
 *
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************/

/*
 * This could very nicely run after unconstrained variable elmination. If we
 *traversed from
 * the root node, we could stop traversing whenever we met a node that wasn't an
 *AND or OR, then
 * we'd just check the number of parents of each boolean symbol that we found.
 *
 * I'm not sure that I've gotten all the polarities sorted.
 */

#ifndef FINDPURELITERALS_H_
#define FINDPURELITERALS_H_

#include "stp/AST/AST.h"
#include "stp/STPManager/STPManager.h"
#include "stp/Simplifier/Simplifier.h"
#include <map>

namespace stp
{
using std::map;

class FindPureLiterals // not copyable
{
  typedef char polarity_type;
  const static polarity_type truePolarity = 1;
  const static polarity_type falsePolarity = 2;
  const static polarity_type bothPolarity = 3;

  map<ASTNode, polarity_type> nodeToPolarity;

  int swap(polarity_type polarity);

public:
  FindPureLiterals() {}
  virtual ~FindPureLiterals() {}

  // Build the polarities, then iterate through fixing them.
  bool topLevel(ASTNode& n, Simplifier* simplifier, STPMgr* stpMgr);

  void build(const ASTNode& n, polarity_type polarity);
};
}
#endif /* FINDPURELITERALS_H_ */
