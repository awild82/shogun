/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Sergey Lisitsyn, Soeren Sonnenburg, Evan Shelhamer, Yuyu Zhang
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <shogun/lib/config.h>

#include <shogun/lib/common.h>
#include <shogun/base/SGObject.h>
#include <shogun/features/Features.h>

namespace shogun
{

/** @brief class Converter used to convert data
 *
 */
class CConverter : public CSGObject
{
public:
	/** constructor */
	CConverter() : CSGObject() {};

	/** destructor */
	virtual ~CConverter() {};

	/** get name */
	virtual const char* get_name() const { return "Converter"; }

	/** applies to the given data, returning converted features
	 * (e.g. dense embedding of string features)
	 * @param features features to convert
	 * @return converted features
	 */
	virtual CFeatures* apply(CFeatures* features) = 0;
};
}
#endif /* CONVERTER_H_ */

