#pragma once

#include <vector>

#include "Mesh.hpp"

std::vector<Coro::Vertex> vertices{
    {{-0.5f, -0.5f, -0.5f}, {.6f, .3f, .9f}, {0.0f, 0.0f}},
    {{
         0.5f,
         -0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         0.0f,
     }},
    {{
         0.5f,
         0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         1.0f,
     }},
    {{-0.5f, 0.5f, -0.5f}, {.6f, .3f, .9f}, {0.0f, 1.0f}},

    {{-0.5f, -0.5f, 0.5f}, {.6f, .3f, .9f}, {0.0f, 0.0f}},
    {{
         0.5f,
         -0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         0.0f,
     }},
    {{
         0.5f,
         0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         1.0f,
     }},
    {{-0.5f, 0.5f, 0.5f}, {.6f, .3f, .9f}, {0.0f, 1.0f}},

    {{-0.5f, 0.5f, 0.5f}, {.6f, .3f, .9f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, -0.5f}, {.6f, .3f, .9f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {.6f, .3f, .9f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {.6f, .3f, .9f}, {0.0f, 0.0f}},

    {{
         0.5f,
         0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         0.0f,
     }},
    {{
         0.5f,
         0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         1.0f,
     }},
    {{
         0.5f,
         -0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         0.0f,
         1.0f,
     }},
    {{
         0.5f,
         -0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         0.0f,
         0.0f,
     }},

    {{-0.5f, -0.5f, -0.5f}, {.6f, .3f, .9f}, {0.0f, 1.0f}},
    {{
         0.5f,
         -0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         1.0f,
     }},
    {{
         0.5f,
         -0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         0.0f,
     }},
    {{-0.5f, -0.5f, 0.5f}, {.6f, .3f, .9f}, {0.0f, 0.0f}},

    {{-0.5f, 0.5f, -0.5f}, {.6f, .3f, .9f}, {0.0f, 1.0f}},
    {{
         0.5f,
         0.5f,
         -0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         1.0f,
     }},
    {{
         0.5f,
         0.5f,
         0.5f,
     },
     {.6f, .3f, .9f},
     {
         1.0f,
         0.0f,
     }},
    {{-0.5f, 0.5f, 0.5f}, {.6f, .3f, .9f}, {0.0f, 0.0f}},
};