# GitHub Activity CLI

This is a simple command-line interface (CLI) application that retrieves and displays the recent activity of a GitHub user.

## Features

* **Retrieves user activity:** Fetches recent activities of a specified GitHub user using the GitHub API.
* **Displays activity in the terminal:**  Presents a clear and concise list of the user's recent activities.
* **Handles errors:** Gracefully manages errors such as invalid usernames or API failures.
* **No external libraries:** Utilizes only standard libraries for retrieving and processing data from the GitHub API.

## Usage

To use the CLI, run the following command, replacing `<username>` with the desired GitHub username:

```bash
hub-activity <username>

For example: hub-activity DioXmio
```

## Output
The CLI will display a list of the user’s recent activities in the terminal, such as:
~~~
5 - git branches or tags created.
1 - git branches or tags were deleted.
1 - repositories were forked.
2 - pull requests were created.
21 - commits were pushed to a repository branch or tag.
~~~

## Contribution Guidelines
Contributions are welcome! Please open an issue to discuss proposed changes and submit pull requests with clear descriptions of the changes made.

This project aims to provide a simple and efficient CLI tool for viewing recent GitHub user activity. Feel free to explore, experiment, and contribute to make it even more useful.


## Disclaimer:
This project is for educational and demonstration purposes only. It’s important to respect GitHub’s API terms of service and usage guidelines.


## The terms of the task can be viewed on the website:
https://roadmap.sh/projects/github-user-activity
