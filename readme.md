🎮 Console Ping Pong Game (C++)

This is a classic Ping Pong game written in modern C++ for the Windows console. It uses standard console functions to draw paddles, move the ball, and track scores, recreating a simple two-paddle pong experience directly in your terminal window.

🚀 Features:

✅ Smooth ball movement and bouncing
✅ Player-controlled left paddle (using W and S keys)
✅ Player-controlled right paddle (using arrow keys)
✅ Score tracking
✅ Top and bottom border collision (ball bounces back)
✅ Game over only when you miss the ball on the left side
✅ Simple text-based console menu
✅ In-game help
✅ Clean, understandable C++ code with clear comments

🎮 Controls:

W → move left paddle up
S → move left paddle down
Arrow Up → move right paddle up
Arrow Down → move right paddle down
Esc → exit gameplay / return to menu

🛠 How It Works:

The game runs in a continuous loop.
The ball moves automatically, bouncing off the top and bottom walls.
If the ball hits a paddle, it bounces back in the opposite horizontal direction.
If the ball goes past the left paddle, the game is over and your score is displayed.
The right paddle can miss but the ball will still reflect from the right edge (no loss on the right).
You can return to the menu any time by pressing Esc.

File Structure

pingpong/
├── app.cpp        # main C++ source code (this file)
└── README.md      # this description

How to Compile and run:

g++ app.cpp -o pingpong
pingpong.exe


