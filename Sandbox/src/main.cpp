#include <Coro/Coro.hpp>

constexpr int W = 1280;
constexpr int H = 720;
constexpr char TITLE[] = "Coro";

class SandboxApp : public Coro::Application
{
public:
    using Application::Application;

private:
    static const int GRID_X = 10;
    static const int GRID_Y = 24;
    const float _pixelSize = static_cast<float>(H) / GRID_Y; // at 720p should be 30.f
    const float _pixelsX = W / _pixelSize;
    const float _pixelsY = H / _pixelSize;

    const float _offsetX = (_pixelsX - GRID_X) / 2 * _pixelSize;
    char _board[GRID_X][GRID_Y] = {'#'};

    float _dropCooldown = 0.f;
    float _moveCooldown = 0.f;

    void SpawnL() {
        const int top = GRID_Y - 1;
        const int mid = GRID_X / 2;

        _board[mid][top] = '.';
        _board[mid][top - 1] = '.';
        _board[mid][top - 2] = '.';
        _board[mid + 1][top - 2] = '.';
    }

    void SpawnT() {
        const int top = GRID_Y - 1;
        const int mid = GRID_X / 2;

        _board[mid][top] = '.';
        _board[mid][top - 1] = '.';
        _board[mid - 1][top - 1] = '.';
        _board[mid + 1][top - 1] = '.';
    }

    void SpawnI() {
        const int top = GRID_Y - 1;
        const int mid = GRID_X / 2;

        _board[mid][top] = '.';
        _board[mid][top - 1] = '.';
        _board[mid][top - 2] = '.';
        _board[mid][top - 3] = '.';
    }

    void DropDown() {
        bool transformToStatic = false;
        for (int y = 0; y < GRID_Y; y++) {
            for (auto& x : _board) {
                if (x[y] == '.') {
                    if (y == 0 || x[y - 1] == 'S') {
                        transformToStatic = true;
                        break;
                    }
                }
            }
        }

        for (int y = 0; y < GRID_Y; y++) {
            for (auto& x : _board) {
                if (x[y] == '.') {
                    if (transformToStatic) {
                        x[y] = 'S';
                    }
                    else {
                        x[y] = '#';
                        x[y - 1] = '.';
                    }
                }
            }
        }
    }

    void MoveLeft() {
        if (_moveCooldown < .1f) return;
        _moveCooldown = 0.f;
        for (int x = 0; x < GRID_X; x++) {
            for (int y = 0; y < GRID_Y; y++) {
                if (_board[x][y] == '.' ) {
                    if (x == 0 || _board[x - 1][y] == 'S') return;
                    _board[x][y] = '#';
                    _board[x-1][y] = '.';
                }
            }
        }
    }

    void MoveRight() {
        if (_moveCooldown < .1f) return;
        _moveCooldown = 0.f;
        const int right = GRID_X - 1;
        for (int x = right; x >= 0; x--) {
            for (int y = 0; y < GRID_Y; y++) {
                if (_board[x][y] == '.') {
                    if (x == right || _board[x+1][y] == 'S') return;
                    _board[x][y] = '#';
                    _board[x + 1][y] = '.';
                }
            }
        }
    }

    bool OnUserCreate() override {
        std::fill(&_board[0][0], &_board[0][0] + sizeof(_board), '#');

        return true;
    };

    bool OnUserUpdate(float delta) override {
        if (Coro::Input::IsKeyPressed(Coro::Key::ESCAPE)) Quit();
        if (Coro::Input::IsKeyPressed(Coro::Key::T)) SpawnT();
        if (Coro::Input::IsKeyPressed(Coro::Key::I)) SpawnI();
        if (Coro::Input::IsKeyPressed(Coro::Key::L)) SpawnL();
        if (Coro::Input::IsKeyPressed(Coro::Key::RIGHT)) MoveRight();
        if (Coro::Input::IsKeyPressed(Coro::Key::LEFT)) MoveLeft();
        if (Coro::Input::IsKeyPressed(Coro::Key::DOWN)) _dropCooldown += .25f;

        _dropCooldown += delta;
        _moveCooldown += delta;
        if (_dropCooldown >= 1.f) {
            _dropCooldown = 0.f;
            DropDown();
        }

        for (int x = 0; x < GRID_X; x++) {
            for (int y = 0; y < GRID_Y; y++) {
                if (_board[x][y] == '#') {
                    DrawPixel(_pixelSize, _pixelSize, _pixelSize * x + _offsetX, _pixelSize * y, .5f, .5f, .5f);
                } else if (_board[x][y] == '.') {
                    DrawPixel(_pixelSize, _pixelSize, _pixelSize * x + _offsetX, _pixelSize * y, .1f, .7f, .9f);
                }
                else if (_board[x][y] == 'S') {
                    DrawPixel(_pixelSize, _pixelSize, _pixelSize * x + _offsetX, _pixelSize * y, .1f, .9f, .4f);
                }
            }
        }

        return true;
    };

};

int main() {
    SandboxApp app{ TITLE, W, H };
    app.Run();

    return 0;
}