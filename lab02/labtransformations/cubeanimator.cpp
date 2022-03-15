/*********************************************************************
 *  Author  : Javierre Borja
 *  Init    : Thursday, January 28, 2022 
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labtransformations/cubeanimator.h>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo CubeAnimator::processorInfo_
{
    "org.inviwo.CubeAnimator",      // Class identifier
    "Cube Animator",                // Display name
    "KTH Labs",                 // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo CubeAnimator::getProcessorInfo() const
{
    return processorInfo_;
}


CubeAnimator::CubeAnimator()
    :Processor()
    // Ports
    , meshIn_("meshIn")
    , meshOut_("meshOut")
    // Properties 
    // For a FloatProperty 
    // variablename(identifier, display name, init value, minvalue, maxvalue)
    , radius_("radius", "Radius", 6, 1, 8)
    , rotation_("rotation", "Rotation", 0, 0, 8)
    , delta_("delta", "delta", 0, 0, 1)
    {
    // Add ports
    addPort(meshIn_);
    addPort(meshOut_);
    
    // Add properties
    addProperty(radius_);
    addProperty(rotation_);
    addProperty(delta_);
}

void CubeAnimator::process()
{
    // Clone the input mesh
    if (!meshIn_.getData()) return;
    auto mesh = meshIn_.getData()->clone();

    // Get the matrix that defines where the mesh is currently
    auto matrix = mesh->getWorldMatrix();
    
    //Getting the time
    std::time_t result = std::time(nullptr);

    float newX = glm::sin(radius_.get()); 

    // Transform the mesh
    matrix = glm::translate(vec3(newX, 0, 0)) * matrix; //get resulting matrix after applying the translation
    matrix = glm::rotate(rotation_.get(), vec3(0, 0, 1)) * matrix; //get resulting matrix after applying the rotation

    // Update
    mesh->setWorldMatrix(matrix);
	
    // Set output
    meshOut_.setData(mesh);
}

} // namespace

