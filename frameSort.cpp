#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Frame
{
    int frame_no;
    string data;
};

bool compareFrames(const Frame &a, const Frame &b)
{
    return a.frame_no < b.frame_no;
}

int main()
{
    int n;
    cout << "Enter number of frames: ";
    cin >> n;

    vector<Frame> frames(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter frame no & data for frame " << i + 1 << ": ";
        cin >> frames[i].frame_no >> frames[i].data;
    }

    cout << "\nFrames received (unordered):\n";
    for (const auto &f : frames)
    {
        cout << "Frame " << f.frame_no << " -> " << f.data << endl;
    }

    sort(frames.begin(), frames.end(), compareFrames);

    cout << "\nFrames after sorting (in correct order):\n";
    for (const auto &f : frames)
    {
        cout << "Frame " << f.frame_no << " -> " << f.data << endl;
    }

    return 0;
}

/*
Example Input/Output:
Enter number of frames: 3
Enter frame no & data for frame 1: 121 Hello
Enter frame no & data for frame 2: 127 World
Enter frame no & data for frame 3: 125 C++

Frames received (unordered):
Frame 121 -> Hello
Frame 127 -> World
Frame 125 -> C++

Frames after sorting (in correct order):
Frame 121 -> Hello
Frame 125 -> C++
Frame 127 -> World
*/