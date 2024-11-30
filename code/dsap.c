// NAME : MEGHA BHAT
// EMAIL : meghajbhat@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SONGS 1000

typedef struct Song {
    char title[100];
    char artist[100];
    char genre[50];
    char youtubeVideoId[20];
    int isFromYouTube; // 0 for CSV, 1 for YouTube
    struct Song *next; // Pointer to the next song in the list
    struct Song *prev; // Added: Pointer to the previous song in the list
} Song;

typedef struct Playlist {
    Song *head; // Pointer to the first song in the list
    Song *tail; // Added: Pointer to the last song in the list
    int numSongs; // Keeps track of the number of songs in the playlist
} Playlist;

typedef struct PlayedSong {
    Song song;
    struct PlayedSong *next;
} PlayedSong;

typedef struct User {
    char name[100];
    char username[100];
    char password[100];
    Playlist playlist; // Contains a linked list of songs
    PlayedSong *playedSongs; // Stack or list of played songs
} User;

Song *globalSongListHead = NULL; // Pointer to the first song in the global song list
int totalSongs = 0; // Keeps track of the total number of songs in the global list

void pushPlayedSong(User *user, Song song) {
    PlayedSong *newPlayedSong = (PlayedSong*)malloc(sizeof(PlayedSong));
    if (newPlayedSong == NULL) {
        printf("Failed to allocate memory for new played song.\n");
        return;
    }
    newPlayedSong->song = song;
    newPlayedSong->next = user->playedSongs;
    user->playedSongs = newPlayedSong;
}

void readCSVFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File could not be opened.\n");
        return;
    }

    char line[256];
    Song *lastSong = NULL;
    while (fgets(line, sizeof(line), file)) {
        Song *newSong = (Song*)malloc(sizeof(Song));
        if (!newSong) {
            printf("Memory allocation failed.\n");
            break;
        }

        char *token = strtok(line, ",");
        if (token) strcpy(newSong->title, token);

        token = strtok(NULL, ",");
        if (token) strcpy(newSong->artist, token);

        token = strtok(NULL, "\n");
        if (token) strcpy(newSong->genre, token);

        newSong->next = NULL;
        newSong->prev = lastSong;
        if (lastSong != NULL) {
            lastSong->next = newSong;
        } else {
            globalSongListHead = newSong; // Set head for the first song
        }
        lastSong = newSong;
        totalSongs++;
    }

    fclose(file);
}
int login(User *users, int numUsers) {
    char username[100];
    char password[100];

    printf("Please log in:\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful, welcome %s!\n", users[i].name);
            return i;
        }
    }

    printf("Login failed. Incorrect username or password.\n");
    return -1;
}
int signup(User *users, int numUsers) {
    char name[100];
    char username[100];
    char password[100];

    printf("Please sign up:\n");
    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline character

    printf("Choose a username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Choose a password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0) {
            printf("Username is already taken. Please choose a different one.\n");
            return -1;
        }
    }

    int index = numUsers;
    strncpy(users[index].name, name, sizeof(users[index].name));
    strncpy(users[index].username, username, sizeof(users[index].username));
    strncpy(users[index].password, password, sizeof(users[index].password));

    // Initialize the user's playlist
    users[index].playlist.head = NULL;
    users[index].playlist.tail = NULL;
    users[index].playlist.numSongs = 0;

    printf("Account created successfully, welcome %s!\n", name);
    return index;
}

void addSongToPlaylist(User *user, int fromYouTube) {
    Song *newSong = (Song*)malloc(sizeof(Song));		//memory allocation
    if (!newSong) {
        printf("Failed to allocate memory for new song.\n");
        return;
    }

    // Set up the new song node
    newSong->next = NULL;
    newSong->prev = user->playlist.tail;			//ptr to current tail

    if (fromYouTube) {		//if from youtube
        // Code to add song from YouTube
        printf("Enter YouTube video title: ");
        fgets(newSong->title, 100, stdin);
        newSong->title[strcspn(newSong->title, "\n")] = 0;

        printf("Enter YouTube video artist: ");
        fgets(newSong->artist, 100, stdin);
        newSong->artist[strcspn(newSong->artist, "\n")] = 0;

        printf("Enter YouTube video ID: ");
        fgets(newSong->youtubeVideoId, 20, stdin);
        newSong->youtubeVideoId[strcspn(newSong->youtubeVideoId, "\n")] = 0;

        // Set the genre to "YouTube" and flag to 1 (indicating it's from YouTube)
        strcpy(newSong->genre, "YouTube");
        newSong->isFromYouTube = 1;
    } else {			//if false
        // Logic to add song from the globalSongList
        printf("Available Songs:\n");
        Song *currentSong = globalSongListHead;
        int songNumber = 1;
        while (currentSong != NULL) {
            printf("%d: %s - %s [%s]\n", songNumber, currentSong->title, currentSong->artist, currentSong->genre);
            currentSong = currentSong->next;
            songNumber++;
        }

        printf("Select a song number to add to your playlist: ");
        int choice, i = 1;
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        currentSong = globalSongListHead;
        while (currentSong != NULL && i < choice) {
            currentSong = currentSong->next;
            i++;
        }

        if (currentSong != NULL && i == choice) {
            strcpy(newSong->title, currentSong->title);
			strcpy(newSong->artist, currentSong->artist);
			strcpy(newSong->genre, currentSong->genre);

            newSong->isFromYouTube = 0; // Set flag to 0 (indicating it's from CSV)
        } else {
            printf("Invalid song choice.\n");
            free(newSong); // Important to free allocated memory if not using it
            return;
        }
    }

    // Inserting the new song into the playlist
    if (user->playlist.tail != NULL) {
        user->playlist.tail->next = newSong;
    } else {
        user->playlist.head = newSong; // For an empty list
    }
    user->playlist.tail = newSong;

    user->playlist.numSongs++;
    printf("'%s' by %s added to your playlist.\n", newSong->title, newSong->artist);			//confirmation
}

void listSongsInPlaylist(const Playlist *playlist) {
    if (playlist->head == NULL) {			
        printf("The playlist is empty.\n");
        return;
    }

    printf("Playlist Songs:\n");
    Song *currentSong = playlist->head;
    int songNumber = 1;
    while (currentSong != NULL) {
        printf("%d: %s by %s [%s]\n", songNumber, currentSong->title, currentSong->artist, currentSong->genre);
        currentSong = currentSong->next;
        songNumber++;
    }
}

void shufflePlaylist(Playlist *playlist) {
    if (playlist->head == NULL || playlist->head->next == NULL) {
        printf("Playlist is too short to shuffle.\n");
        return;
    }

    srand(time(NULL));
    int numSongs = playlist->numSongs;
    Song *songs[numSongs]; // Array of pointers to the songs

    // Fill the array with pointers to the songs
    Song *currentSong = playlist->head;
    for (int i = 0; i < numSongs; i++) {
        songs[i] = currentSong;
        currentSong = currentSong->next;
    }

    // Shuffle the array of pointers			
    for (int i = 0; i < numSongs; i++) {
        int j = rand() % numSongs;
        Song *temp = songs[i];
        songs[i] = songs[j];
        songs[j] = temp;
    }

    // Reconstruct the playlist with the shuffled order
    playlist->head = songs[0];
    playlist->tail = songs[numSongs - 1];
    for (int i = 0; i < numSongs - 1; i++) {
        songs[i]->next = songs[i + 1];
        songs[i + 1]->prev = songs[i];
    }
    songs[0]->prev = NULL;
    songs[numSongs - 1]->next = NULL;

    printf("Playlist shuffled.\n");
}

void deleteSong(Playlist *playlist, int index) {
    if (index < 0 || index >= playlist->numSongs) {
        printf("Invalid index for deletion.\n");
        return;
    }

    Song *currentSong = playlist->head;
    for (int i = 0; i < index; i++) {
        currentSong = currentSong->next;
    }

    if (currentSong->prev) {
        currentSong->prev->next = currentSong->next;
    } else {
        playlist->head = currentSong->next; // Deleting the first song
    }

    if (currentSong->next) {
        currentSong->next->prev = currentSong->prev;
    } else {
        playlist->tail = currentSong->prev; // Deleting the last song
    }

    free(currentSong);
    playlist->numSongs--;
    printf("Deleted song at index %d\n", index + 1);
}
Song *currentPlayingSong = NULL; // Global variable for the current song

void showCurrentSong() {
    if (currentPlayingSong != NULL) {
        printf("\nCurrently playing:\n");
        printf("Title: %s\n", currentPlayingSong->title);
        printf("Artist: %s\n", currentPlayingSong->artist);
        printf("Genre: %s\n", currentPlayingSong->genre);
        if (currentPlayingSong->isFromYouTube) {
            printf("YouTube Video ID: %s\n", currentPlayingSong->youtubeVideoId);
        }
    } else {
        printf("\nNo song is currently playing.\n");
    }
}

void playNext(User *user, Song *now_playing) {
    Playlist *playlist = &(user->playlist);

    if (playlist->head != NULL) {
        // Copy the details of the currently playing song
        *now_playing = *playlist->head;

        // Update the global currentPlayingSong
        currentPlayingSong = now_playing;

        printf("Now playing: %s by %s (%s)\n", now_playing->title, now_playing->artist, now_playing->genre);

        // Push the current song to the playedSongs stack before deleting it from the playlist
        pushPlayedSong(user, *playlist->head);

        // Then delete the song from the head of the playlist
        Song *temp = playlist->head;
        playlist->head = playlist->head->next;
        if (playlist->head) {
            playlist->head->prev = NULL;
        } else {
            playlist->tail = NULL; // If the playlist becomes empty
        }
        free(temp);
        playlist->numSongs--;

        // If the playlist is now empty, reset currentPlayingSong
        if (playlist->head == NULL) {
            currentPlayingSong = NULL;
        }
    } else {
        printf("Your playlist is empty. Add songs to play.\n");
        currentPlayingSong = NULL; // Resetting as there's no song to play
    }
}

void recommendSong() {
    if (totalSongs > 0) {
        int randomIndex = rand() % totalSongs;
        Song *currentSong = globalSongListHead;
        for (int i = 0; i < randomIndex && currentSong != NULL; i++) {
            currentSong = currentSong->next;
        }

        if (currentSong != NULL) {
            printf("Recommended song: '%s' by %s\n", currentSong->title, currentSong->artist);
        } else {
            printf("Error in song recommendation.\n");
        }
    } else {
        printf("No songs available to recommend.\n");
    }
}


Song popPlayedSong(User *user) {
    if (user->playedSongs == NULL) {
        printf("No previous song to play.\n");
        return (Song){0}; // Return an empty song structure
    }
    PlayedSong *topPlayedSong = user->playedSongs;
    user->playedSongs = topPlayedSong->next;
    Song song = topPlayedSong->song;
    free(topPlayedSong);
    return song;
}

void playPrevious(User *user) {
    Song previousSong = popPlayedSong(user);
    if (previousSong.title[0] != '\0') { // Check if the song is not empty
        printf("Now playing previous song: %s by %s (%s)\n", previousSong.title, previousSong.artist, previousSong.genre);
    }
}


void show_song_details(const Song *now_playing) {
    if (now_playing == NULL) {
        printf("No song is currently playing.\n");
    } else {
        printf("\n----------------------------------------------------------------------\n");
        printf("                          DETAILED OVERVIEW\n");
        printf("----------------------------------------------------------------------\n");
        printf("\t   TITLE    |   %s\n", now_playing->title);
        printf("\t   ARTIST   |   %s\n", now_playing->artist);
        if (now_playing->isFromYouTube) {
            printf("\t   VIDEO ID |   %s\n", now_playing->youtubeVideoId);
        } else {
            printf("\t   GENRE    |   %s\n", now_playing->genre);
        }
        printf("----------------------------------------------------------------------\n");

        printf("<<<<< Enter any input to return to MAIN MENU\n");
        char leave[100];
        if (scanf("%s", leave)) {
            // Consider removing system("clear") for portability and security reasons
            // You might replace it with a portable and safe alternative
        }
    }
}

void searchSongOnYoutube(User *user) {
    char query[100];
    printf("Enter search query: ");
    fgets(query, 100, stdin);
    query[strcspn(query, "\n")] = 0; // Remove newline character

    char command[256];
    sprintf(command, "python \"C:/Users/Meghabhat/Desktop/CODE LANGS/C/music playlist generator/youtube_search.py\" \"%s\"", query);
    system(command);

    printf("Would you like to add a song from the search results to your playlist? (y/n): ");
    char choice;
    scanf("%c", &choice);
    getchar(); // Consume the newline character

    if (choice == 'y' || choice == 'Y') {
        addSongToPlaylist(user, 1);  // 1 indicates adding from YouTube
    }
}

int main() {
    srand(time(NULL));
    User users[10];
    int numUsers = 0;
    int loggedInUser = -1;

    readCSVFile("C:/Users/Meghabhat/Desktop/CODE LANGS/C/music playlist generator/corrected_songs.csv");  // Update with the actual path to your CSV file

    while (1) {
        printf("\n----------------------------------------------\n");
        printf("              MUSIC PLAYER MENU               \n");
        printf("----------------------------------------------\n");
        printf("1.  Login\n");
        printf("2.  Sign Up\n");
        printf("3.  Add Song to Playlist\n");
        printf("4.  List Songs in Playlist\n");
        printf("5.  Delete Song\n");
        printf("6.  Shuffle Playlist\n");
        printf("7.  Play Next\n"); 
        printf("8.  Recommend Song\n");
        printf("9.  Play Previous\n");
        printf("10. Search Song on YouTube\n");
        printf("11. Show Current Song\n"); 
        printf("12. Exit\n");
        printf("----------------------------------------------\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                loggedInUser = login(users, numUsers);
                break;
            case 2:
                if (numUsers < 10) {
                    int result = signup(users, numUsers);
                    if (result >= 0) {
                        loggedInUser = result;
                        numUsers++;
                    }
                } else {
                    printf("Maximum number of users reached.\n");
                }
                break;
            case 3:
                if (loggedInUser >= 0) {
                    addSongToPlaylist(&users[loggedInUser], 0); // 0 indicates adding from local database
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 4:
                if (loggedInUser >= 0) {
                    listSongsInPlaylist(&users[loggedInUser].playlist);
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 5:
                if (loggedInUser >= 0 && users[loggedInUser].playlist.numSongs > 0) {
                    int index;
                    printf("Enter the number of the song to delete (1-%d): ", users[loggedInUser].playlist.numSongs);
                    scanf("%d", &index);
                    getchar(); // to consume the newline character

                    if (index > 0 && index <= users[loggedInUser].playlist.numSongs) {
                        deleteSong(&users[loggedInUser].playlist, index - 1); // Adjusting for zero-based index
                        printf("Deleted song number %d from your playlist.\n", index);
                    } else {
                        printf("Invalid song number.\n");
                    }
                } else {
                    printf("Your playlist is empty or please login first.\n");
                }
                break;
            case 6:
                if (loggedInUser >= 0) {
                    shufflePlaylist(&users[loggedInUser].playlist);
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 7:
                if (loggedInUser >= 0) {
                    Song now_playing;
                    playNext(&users[loggedInUser], &now_playing);
                    show_song_details(&now_playing);
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 8:
                recommendSong();
                break;
            case 9:
                if (loggedInUser >= 0) {
                    playPrevious(&users[loggedInUser]);
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 10:
                if (loggedInUser >= 0) {
                    searchSongOnYoutube(&users[loggedInUser]);
                } else {
                    printf("Please login first.\n");
                }
                break;
            case 11:
                showCurrentSong();
                break;
            case 12:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
    return 0;
}