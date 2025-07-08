#include "trpch.h"
#include "Game.h"
#include "Input.h"

#include "DeltaTime.h"

Game::Game()
    :m_camera(-1600, 1600, -900, 900), m_map(100,100)
{
    LoadAssets();
    m_camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    m_camera.SetRotation(0.0f);

    m_TextureShader = std::make_shared<Shader>("assets/shaders/TextureShader.vert", "assets/shaders/TextureShader.frag");

    m_player.SetPlayerPositionBasedOnBlocks(glm::vec3(0, m_map.getHeightBasedOnX(0) + m_player.GetPlayerHeight(), 0));

    imguiAPI = new ImGuiAPI();
}

Game::~Game()
{
    imguiAPI->Close();
}

void Game::update()
{
    glm::vec2 CursorPos = m_player.GetMousePosBasedOnBlocks(m_camera.GetViewProjectionMatrix(), App::Get().GetWindow().GetWidth(), App::Get().GetWindow().GetHeight());

    handleInput();
    m_player.update();
    AttachCameraToPlayer(attachCameraToPlayer); 
    //LOG_WARN("{0},{1},{2}", m_player.GetPlayerPositionBasedOnBlocks().x, m_player.GetPlayerPositionBasedOnBlocks().y, m_player.GetPlayerPositionBasedOnBlocks().z);
}

void Game::render()
{
    m_TextureShader->use();
    m_TextureShader->setMat4("u_ViewProjection", m_camera.GetViewProjectionMatrix());
    m_map.render(m_TextureShader);
    m_player.render(m_TextureShader);

    //IMGUI
    glm::vec2 CursorPos = m_player.GetMousePosBasedOnBlocks(m_camera.GetViewProjectionMatrix(), App::Get().GetWindow().GetWidth(), App::Get().GetWindow().GetHeight());
    glm::vec3 playerPos = m_player.GetPlayerPositionBasedOnBlocks();
    imguiAPI->Begin();
    ImGui::Begin("Test Window");
    ImGui::Text("FPS: %.1f", 1.0f / DeltaTime::getDeltaTime());
    ImGui::Text("Player pos: (%.1f, %.1f, %.1f)", playerPos.x, playerPos.y, playerPos.z);
    ImGui::Text("Cursor pos: (%.1f, %.1f)", CursorPos.x, CursorPos.y);
    ImGui::Text("Current Block: %s", charToBlockName(currentBlock).c_str());
    ImGui::End();
    imguiAPI->End();
    //
}

void Game::AttachCameraToPlayer(bool x)
{
    if (x)
    {
        m_camera.SetPosition(m_player.GetPosition());
    }
}

void Game::handleInput()
{
    glm::vec2 CursorPos = m_player.GetMousePosBasedOnBlocks(m_camera.GetViewProjectionMatrix(), App::Get().GetWindow().GetWidth(), App::Get().GetWindow().GetHeight());

    if (Input::OnkeyPressed(GLFW_KEY_C))
    {
        attachCameraToPlayer = !attachCameraToPlayer;
    }
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        m_map.EraseBlockAtPos(CursorPos.x, CursorPos.y);
    }
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        m_map.PlaceBlockAtPos(CursorPos.x, CursorPos.y, currentBlock);
    }

    if (Input::OnScrollUp())
    {
        BlockIterator == blocksCharacterType.size() - 1 ? BlockIterator = 0 : BlockIterator++;
    }
    if (Input::OnScrollDown())
    {
        BlockIterator == 0 ? BlockIterator = blocksCharacterType.size() - 1 : BlockIterator--;
    }

    currentBlock = blocksCharacterType[BlockIterator];
}

std::string Game::charToBlockName(char blockChar)
{
    switch (blockChar)
    {
    case 'A': return "AIR";
    case 'G': return "GRASS";
    case 'X': return "DIRT";
    case 'S': return "STONE";
    case 'W': return "SAND";
    default: return "undefined: " + std::string(1, blockChar);
    }
}
