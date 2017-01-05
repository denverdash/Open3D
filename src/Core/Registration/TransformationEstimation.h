// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 Qianyi Zhou <Qianyi.Zhou@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <Eigen/Core>

namespace three {

class PointCloud;

/// Base class that estimates a transformation between two point clouds
/// The virtual function ComputeTransformation() must be implemented in
/// subclasses.
class TransformationEstimation
{
public:
	typedef std::pair<int, int> Correspondence;
	typedef std::vector<Correspondence> CorrespondenceSet;

public:
	TransformationEstimation() {}
	virtual ~TransformationEstimation() {}

public:
	virtual double ComputeError(const PointCloud &source,
			const PointCloud &target, const CorrespondenceSet &corres) = 0;
	virtual Eigen::Matrix4d ComputeTransformation(const PointCloud &source,
			const PointCloud &target, const CorrespondenceSet &corres) = 0;
};

/// Estimate a transformation for point to point distance
class TransformationEstimationPointToPoint : public TransformationEstimation
{
public:
	TransformationEstimationPointToPoint(bool with_scaling = false) :
		with_scaling_(with_scaling) {}
	~TransformationEstimationPointToPoint() override {}

public:
	double ComputeError(const PointCloud &source, const PointCloud &target,
			const CorrespondenceSet &corres) final;
	Eigen::Matrix4d ComputeTransformation(const PointCloud &source,
			const PointCloud &target, const CorrespondenceSet &corres) final;

private:
	bool with_scaling_ = false;
};

}	// namespace three