#include "window.h"
#include <iostream>
#include <locale.h>

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
    setlocale(LC_CTYPE, "Polish");
    this->comic_sans.loadFromFile("src/fonts/ComicSansMS3.ttf");
    this->window_title = title;
    this->window_size = size;
    this->is_done = false;
    this->is_fullscreen = false;
    this->in_lobby = true;
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
        //std::cout<<"ZAMKNIETO OKNO!\n";
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

void Window::DrawTileCollection(const TileManager& tile_manager, int current_ferdek_column)
{
    int x = tile_manager.GetTiles().size();
    int y = tile_manager.GetTiles()[0].size();
    for(int i=std::max(0, current_ferdek_column-32);i<std::min(32+current_ferdek_column, x);i++)
    {
        for(int j=0;j<y;j++)
        {
            if(tile_manager.CheckTile(i, j)){
                Draw(tile_manager.GetTiles()[i][j]->GetSprite());

            }
        }
    }
}


void Window::UpdateView(const float& player_x, const float& min_x, const float& max_x)
{
    float top_x = std::max(min_x, player_x-window_size.x/2);
    top_x = std::min(top_x, max_x-window_size.x);
    sf::View view(sf::FloatRect(top_x, 0.f, window_size.x, window_size.y));
    render_window.setView(view);
}

sf::Vector2u Window::GetActualSize()
{
    return render_window.getSize();
}

void Window::DrawMobs(const std::vector<std::shared_ptr<Mob>>& mobs, float ferdek_position_x)
{
    int n = mobs.size();
    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek_position_x-mobs[i]->GetPosition().x)/32 < 24)
        {
            Draw(mobs[i]->GetSprite());

        }
    }
}

void Window::DrawStats(const unsigned int& coins, const int& lives, const float& player_x, const float& min_x, const float& max_x)
{
    float top_x = std::max(min_x, player_x-window_size.x/2);
    top_x = std::min(top_x, max_x-window_size.x);
    sf::Vector2f position(top_x, 0);
    std::wstring content = L" zł";
    content = std::to_wstring(coins)+content;
    sf::Text result_text (content, comic_sans);
    result_text.setCharacterSize(64);
    result_text.setFillColor(sf::Color(255, 255, 0));
    result_text.setPosition(position);
    Draw(result_text);

    content = L"Życia: ";
    content = content + std::to_wstring(lives);
    result_text.setCharacterSize(64);
    result_text.setFillColor(sf::Color::Red);
    result_text.setPosition(position); 
    result_text.setString(content);
    position.x += window_size.x * 0.5f;
    result_text.setPosition(position);
    Draw(result_text);  

}

void Window::StartWindow()
{
    this->in_lobby = true;
    
    sf::RectangleShape startButton(sf::Vector2f(400, 100));
    startButton.setPosition(300, 250);
    startButton.setFillColor(sf::Color::Green);

    UpdateView(0,0,10000);
    sf::Text buttonText("START - kliknij enter", comic_sans, 30);
    buttonText.setPosition(360, 280);
    buttonText.setFillColor(sf::Color::White);

    sf::Text Title("SUPER FERDEK", comic_sans, 60);
    Title.setPosition(360, 80);
    Title.setFillColor(sf::Color::Black);

    //render_window.display();
    while(true)
    {
        BeginDraw();
        Draw(startButton);
        Draw(buttonText);
        Draw(Title);
        sf::Event event;
        while(render_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            is_done = true;
            return;
            //std::cout<<"ZAMKNIETO OKNO!\n";
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::F5)
        {
            ToggleFullscreen();
        }
        else if(event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter)
        {
            this->in_lobby = false;
            return;
        }
        }
        EndDraw();
    }
}

void Window::DrawFerdek(Ferdek& ferdek)
{
    ferdek.set_sprite_origin(0, 32+16*ferdek.get_is_big());
    Draw(ferdek.get_sprite());
}