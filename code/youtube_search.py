# NAME : MEGHA BHAT
# EMAIL : meghajbhat@gmail.com 

import sys
import googleapiclient.discovery

def youtube_search(query):
    # Build the YouTube API service
    youtube = googleapiclient.discovery.build("youtube", "v3", developerKey="AIzaSyACmKaxJJ9cWtmetiAmotJOh5INDiYH7Kk")

    # Perform the search
    request = youtube.search().list(q=query, part="snippet", type="video", maxResults=10)
    response = request.execute()

    # Print search results
    for item in response.get("items", []):
        title = item["snippet"]["title"]
        video_id = item["id"]["videoId"]
        print(f"Title: {title}\nVideo ID: {video_id}\n----------------------------")

if __name__ == "__main__":
    query = sys.argv[1]  # Get the search query from command line argument
    youtube_search(query)