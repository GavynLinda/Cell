#ifndef CELL_MATERIAL_LIBRARY_H
#define CELL_MATERIAL_LIBRARY_H

#include <vector>
#include <map>

namespace Cell
{
    class Material;
    class Renderer;
    class Shader;
    class RenderTarget;

    class MaterialLibrary
    {
        friend Renderer;
    private:
        // holds a list of default material templates that other materials can derive from
        std::map<unsigned int, Material*> m_DefaultMaterials;
        // stores all generated/copied materials
        std::vector<Material*> m_Materials;

        // internal render-specific materials
        Material* defaultBlitMaterial;
        Material* postProcessingMaterial; // TODO(Joey): move to post-processing toolkit

        Shader *deferredAmbientShader;
        Shader* deferredDirectionalShader;
        Shader* deferredPointShader;

        Material *debugLightMaterial;

        // TODO: move these to PBR toolkit
        Material *PBRHdrToCubemap;
        Material *PBRIrradianceCapture;
        Material *PBRPrefilterCapture;
        Material *PBRIntegrateBRDF;

    public:
        MaterialLibrary(RenderTarget *gBuffer);
        ~MaterialLibrary();

        // create either a deferred default material (based on default set of materials available (like glass)), or a custom material (with custom you have to supply your own shader)
        Material* CreateMaterial(std::string base);             // these don't have the custom flag set (default material has default state and uses checkerboard texture as albedo (and black metallic, half roughness, purple normal, white ao)
        Material* CreateCustomMaterial(Shader *shader);         // these have the custom flag set (will be rendered in forward pass)
        Material* CreatePostProcessingMaterial(Shader *shader); // these have the post-processing flag set (will be rendered after deferred/forward pass)
    private:
        // generate all default template materials
        void generateDefaultMaterials();
        // generate all internal materials used by the renderer; run in MaterialLibrary to improve readability.
        void generateInternalMaterials(RenderTarget *gBuffer);
    };
}

#endif