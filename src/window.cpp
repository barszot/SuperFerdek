#include "window.h"

Window::Window()
{
    Setup("Window", sf::Vector2u(512,512));
}

Window::Window(const std::string& title,const sf::Vector2u& size)
{
    Setup(title, size);
}
Window::~Window()
{
    Destroy();
}
void Window::Setup(const std::string& title, const sf::Vector2u& size)
{
    this->window_title = title;
    this->window_size = size;
    this->is_done = false;
    this->is_fullscreen = false;
    render_window.setFramerateLimit(60);
    Create();
}
void Window::Destroy()
{
    render_window.close();
}
void Window::Create()
{
    auto style = (is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    render_window.create({ window_size.x, window_size.y, 32 }, window_title, style);
}

bool Window::IsDone() const
{
    return is_done;
}
bool Window::IsFullscreen() const
{
    return is_fullscreen;
}
sf::Vector2u Window::GetWindowSize() const
{
    return window_size;
}
void Window::BeginDraw() // Clears the window
{
    render_window.clear(sf::Color::Cyan);
}
void Window::EndDraw() //Shows result
{
    render_window.display();
}
void Window::Update()
{
    sf::Event event;
    while(render_window.pollEvent(event)){
    if(event.type == sf::Event::Closed){
        is_done = true;
    }
    else if(event.type == sf::Event::KeyPressed &&
    event.key.code == sf::Keyboard::F5)
    {
        ToggleFullscreen();
    }
    }
}
void Window::ToggleFullscreen()
{
    is_fullscreen = !is_fullscreen;
    Destroy();
    Create();
}
void Window::Draw(const sf::Drawable& drawable)
{
    render_window.draw(drawable);
}
void Window::DrawTile(const Tile& tile)
{
    Draw(tile.GetSprite());
}

void Window::DrawTileCollection(const TileManager& tile_manager)
{
    const std::vector<std::shared_ptr<Tile>>& tile_collection = tile_manager.GetTileCollection();
    int n = tile_collection.size();
    for(int i=0;i<n;i++)
    {
        DrawTile(*tile_collection[i]);
    }
}

void Window::UpdateView(const float& player_x, const float& min_x, const float& max_x)
{
    float top_x = std::max(min_x, player_x-window_size.x/2);
    top_x = std::min(top_x, max_x-window_size.x);
    sf::View view(sf::FloatRect(top_x, 0.f, window_size.x, window_size.y));
    render_window.setView(view);
}