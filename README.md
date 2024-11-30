# Music Playlist Generator

This **Music Playlist Generator** is a C-based program that allows users to manage and enjoy music playlists with features like adding songs, playing tracks, shuffling playlists, and integrating YouTube search for song discovery. It uses a CSV file for local songs and supports dynamic user management and playback functionality.

---

## Features

### User Management
- **Sign Up**: Create a new user account with a username and password.
- **Login**: Authenticate existing users to access their playlists.
  
### Playlist Management
- **Add Songs**: 
  - Add songs from a local CSV database.
  - Add songs directly from YouTube search results.
- **List Songs**: View the songs currently in the playlist.
- **Delete Songs**: Remove specific songs from the playlist.
- **Shuffle Playlist**: Randomize the order of songs in the playlist.

### Playback Controls
- **Play Next**: Play the next song in the playlist and show detailed song information.
- **Play Previous**: Replay recently played songs using a stack-based structure.
- **Show Current Song**: Display details of the currently playing song.

### Song Discovery
- **Recommend Songs**: Suggest random songs from the global song database.
- **YouTube Search Integration**:
  - Search for songs on YouTube via the `youtube_search.py` script.
  - Add selected YouTube songs to the playlist.

---

## Technologies Used

### Programming Language
- **C** (Core application logic and playlist management)
- **Python** (YouTube search integration using the YouTube Data API)

### Tools/Libraries
- **Standard C Libraries**: For memory management, file handling, and linked list operations.
- **YouTube Data API**: Integrated for searching songs on YouTube.

---

## How to Use

### Prerequisites
1. A C compiler (e.g., GCC).
2. Python installed with the `google-api-python-client` library:
   ```bash
   pip install google-api-python-client
3. Compile the C program:
   ```bash
   gcc dsap.c -o music_playlist
4. Run the compiled program:
   ```bash
   ./music_playlist
6. Follow the menu options to manage playlists, play songs, and explore YouTube search.

---

## YouTube Search

To enable YouTube search:

1. Ensure `youtube_search.py` is in the same directory.
2. Replace the placeholder `developerKey` in `youtube_search.py` with your YouTube Data API key.

---

## Features Explained

### Playlist Management

1. **Adding Songs**:
   - Select from a preloaded song list (CSV file) or add songs from YouTube.
2. **Viewing Playlist**:
   - Lists all songs currently in the user’s playlist.
3. **Deleting Songs**:
   - Removes songs from the playlist by their position.

### Playback

- **Play Next**:
  - Plays the first song in the playlist and removes it from the list.
- **Play Previous**:
  - Replays recently played songs stored in a stack.
- **Show Current Song**:
  - Displays detailed information about the currently playing song.

### YouTube Integration

- Search for songs on YouTube and print the top 10 results.
- Add selected YouTube results to the playlist.

---

## Example Usage

1. **Adding a Song**:
   - Option to select a song from the local database or search on YouTube.
   - Example:
     ```
     1: Shape of You - Ed Sheeran [Pop]
     2: Blinding Lights - The Weeknd [Synthwave]
     Enter the song number to add to your playlist: 1
     ```

2. **Playing Songs**:
   - Automatically shows the currently playing song with details.

3. **YouTube Search**:
   - Example:
     ```bash
     Enter search query: Ed Sheeran
     ```
   - Output:
     ```
     Title: Shape of You
     Video ID: JGwWNGJdvx8
     ```

---

## CSV Format

The `corrected_songs.csv` file contains the following fields:

- **Title**: The song's title.
- **Artist**: The performing artist.
- **Genre**: The song's genre.
