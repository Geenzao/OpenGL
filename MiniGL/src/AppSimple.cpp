#include "MiniGL/App.h"

class AppSimple : public mgl::App
{
public:
    AppSimple(int width, int height) : App(width, height, 4, 6) {};

protected:
    void Init() override
    {
        // initialize what needs to be rendered here
        // camera (looks toward +X by default)
        m_camera = std::make_unique<mgl::Camera>(glm::vec3(-6, 2, 0), m_window.AspectRatio(), 70.f, .01f, 1000.f);

        // simple shader
        s.AddShaderFromFile(mgl::gpu::Shader::ShaderSource(mgl::gpu::Shader::Vertex, "shaders/default.vert"));
        s.AddShaderFromFile(mgl::gpu::Shader::ShaderSource(mgl::gpu::Shader::Fragment, "shaders/default.frag"));
        s.Create();

        // scene: a platform (flat slab, top face at y = 0) and a cube resting on it
        m_meshes.push_back(mgl::Mesh::GenerateCube(1.f));
        m_models.push_back(glm::translate(glm::mat4(1.f), glm::vec3(0, -.25f, 0)) * glm::scale(glm::mat4(1.f), glm::vec3(5.f, .25f, 5.f)));
        m_colors.push_back(glm::vec3(.6f, .6f, .65f));

        m_meshes.push_back(mgl::Mesh::GenerateCube(.5f));
        m_models.push_back(glm::translate(glm::mat4(1.f), glm::vec3(0, .5f, 0)));
        m_colors.push_back(glm::vec3(.9f, .35f, .25f));

        mgl::gpu::GLUtils::ClearColor({.2f, .2f, .2f, 1.f});
        mgl::gpu::GLUtils::SetDepthTesting(true);
        mgl::gpu::GLUtils::SetViewportSize(m_window.Width(), m_window.Height());
    }

    void Render() override
    {
        m_gpuDeltaTime.Begin();
        // clear the framebuffer
        mgl::gpu::GLUtils::Clear();

        s.Bind();
        s.UniformData("lightDirection", glm::vec3(1.f, -1.f, -1.f));
        s.UniformData("lightColor", glm::vec3(1.f, 0.f, 0.f));
        s.UniformData("viewMatrix", m_camera->View());
        s.UniformData("projectionMatrix", m_camera->Projection());
        s.UniformData("useTexture", 0);
        for (size_t i = 0; i < m_meshes.size(); i++)
        {
            s.UniformData("modelMatrix", m_models[i]);
            s.UniformData("baseColor", m_colors[i]);
            m_meshes[i].Draw();
        }

        m_gpuDeltaTime.End();
    }

private:
    mgl::gpu::Shader s;
    std::vector<glm::mat4> m_models;
    std::vector<glm::vec3> m_colors;
};
