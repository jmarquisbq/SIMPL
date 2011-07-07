/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Grober (US Air Force Research Laboratories
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _ReconstructionFunc_H
#define _ReconstructionFunc_H

#if defined (_MSC_VER)
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <list>
#include <algorithm>
#include <numeric>

#include <boost/shared_array.hpp>

#include "MXA/MXATypes.h"
#include "MXA/Common/MXASetGetMacros.h"

#include "DREAM3D/DREAM3DConfiguration.h"
#include "DREAM3D/Common/AIMArray.hpp"
#include "DREAM3D/Common/Constants.h"
#include "DREAM3D/Common/Grain.h"
#include "DREAM3D/Common/AIMRandomNG.h"
#include "DREAM3D/Common/OrientationMath.h"
#include "DREAM3D/Common/OrientationOps/CubicOps.h"
#include "DREAM3D/Common/OrientationOps/HexagonalOps.h"
#include "DREAM3D/Common/OrientationOps/OrthoRhombicOps.h"
#include "DREAM3D/ANGSupport/AbstractAngDataLoader.h"
#include "DREAM3D/Reconstruction/ReconstructionVoxel.h"
#include "DREAM3D/HDF5/H5ReconStatsWriter.h"

using namespace std;

/**
 * @class ReconstructionFunc ReconstructionFunc.h AIM/Common/ReconstructionFunc.h
 * @brief This class holds all the various functions that are needed to reconstruct
 * a 3D representation from a stack of OIM Data.
 * @author Michael A. Jackson for BlueQuartz Software
 * @author Michael A. Groeber (US Air Force Research Laboratory)
 * @version 2.0
 */
class DREAM3DLib_EXPORT ReconstructionFunc
{
  public:
    MXA_SHARED_POINTERS(ReconstructionFunc)
    MXA_STATIC_NEW_MACRO(ReconstructionFunc)

    virtual ~ReconstructionFunc();

    typedef boost::shared_array<float>    SharedFloatArray;
    typedef boost::shared_array<int>      SharedIntArray;

    float sizex;
    float sizey;
    float sizez;

    float resx;
    float resy;
    float resz;

    int xpoints;
    int ypoints;
    int zpoints;
    int totalpoints;

    float misorientationtolerance;

    vector<AIM::Reconstruction::CrystalStructure> crystruct;
    vector<AIM::Reconstruction::PhaseType>        phaseType;
    std::vector<float>                            pptFractions;

	std::vector<int> grain_indicies;
    std::vector<int> phases;
    std::vector<float> euler1s;
    std::vector<float> euler2s;
    std::vector<float> euler3s;
    std::vector<int> neighbors;
    std::vector<int> surfacevoxels;
    std::vector<int> alreadychecked;
    std::vector<int> unassigned;
    std::vector<float> confidences;
    std::vector<float> imagequalities;
    std::vector<std::vector<float> > quats;

    SharedIntArray graincounts;
    std::vector<Grain::Pointer> m_Grains;

    float minseedconfidence;
    float minseedimagequality;
    float downsamplefactor;
    int minallowedgrainsize;
    int mergetwinsoption;
    int mergecoloniesoption;

    int alignmeth;
    int alreadyformed;

    int numseNbins;
    int numorients;
    int numeulers;
 //   int numgrains;
    int cutoutxsize;
    int cutoutysize;
    int cmaxx;
    int cminx;
    int cmaxy;
    int cminy;

    int tempxpoints;
    int tempypoints;
    int totaltemppoints;
    int numneighbins;

    void initialize(int nX,
                    int nY,
                    int nZ,
                    float xRes,
                    float yRes,
                    float zRes,
                    bool mrgTwins,
                    bool mrgColonies,
                    int minAllowedGrSize,
                    float minSeedConfidence,
                    float dwnSmplFact,
                    float minImgQlty,
                    float misoTol,
                    vector<AIM::Reconstruction::CrystalStructure> crystalStructures,
                    vector<AIM::Reconstruction::PhaseType> phaseTypes,
                    std::vector<float> precipFractions,
                    int alignmentMethod);


	void initializeQuats();
    void find_border();
    void form_grains();
    void form_grains_sections();
    void remove_smallgrains();
    int renumber_grains1();
    void assign_badpoints();
    void find_neighbors();
    void merge_containedgrains();
    void reorder_grains();
    int remove_smallgrains(size_t numgrains);
	void fillin_sample();
    void cleanup_data();
    void merge_twins();
    void merge_colonies();
    void characterize_twins();
    void characterize_colonies();
    void renumber_grains3();
    void align_sections();

    float gamma(float x);
    float find_xcoord(size_t index);
    float find_ycoord(size_t index);
    float find_zcoord(size_t index);

  protected:
    ReconstructionFunc();

  private:
    std::vector<OrientationMath*>    m_OrientationOps;
    CubicOps::Pointer                m_CubicOps;
    HexagonalOps::Pointer            m_HexOps;
    OrthoRhombicOps::Pointer         m_OrthoOps;

    ReconstructionFunc(const ReconstructionFunc&);    // Copy Constructor Not Implemented
    void operator=(const ReconstructionFunc&);  // Operator '=' Not Implemented
};


#endif
