# Typing-Trainer


# typingTrainer ✌️

Project idea for the Advanced Programming course by Anastasia Golovin anastasia.golovin@tum.de and Mykyta Smyrnov ge78daq@mytum.de. 

## Motivation
In this project, you will create a command line typing trainer, which will help to acquire or improve user's touch typing skills. The program has to be implemented completely in the command line interface of any binary-executable environment. Users can create different user accounts to save their progress. They can choose between several levers of difficulty, starting with the middle row on the basic level to the full layout on the advanced level.


## Sprint 1
### Goal:
Implement the main functionality of the type trainer: display predetermined sample text, process user input, collect, save and display statistics. 
### Definiton of "done"
- The ncurses library is used to create three windows in the terminal: one for sample text, one for user input and one for the error count.
- The program displays sample text in English. The text is loaded from a persistent storage in a .txt file.
- Current position is marked in the sample text. 
- As the user types, the program processes characters as they are typed (using the `getch()` function from the ncurses library). If the user enters a wrong character, the program marks the letter red in the sample text and increases the error count. 
- After each level, the score and the elapsed time are displayed.
- Progress is saved in a .txt file.
### Optional:
- Let the user re-type the whole sentence if she makes a typo. Add a short time delay so that characters typed immediately after the typo are not treated as an error.
- If the user did too many typos, she has to start the level over again. 

## Sprint 2
### Goal:
Add a menu and a possibility to create different accounts. Replace predetermined text by a clever text generator that can handle different difficulty levels. 
### Definiton of "done":
- A menu is shown to the user at the start of the program with the following elements: 
```
    | - new user = (fields: username, difficulty)
    | - delete user; 
    | - load user;
        | - show progress;
        | - change difficulty;
        | - clean progress; 
        | - start practicing; 
            | - back to menu
```
- The user can select between different difficulty levels (beginner, intermediate, advanced).
    - Beginner: lowercase letters from the middle row
    - Intermediate: lower- and uppercase letters from the middle and upper rows
    - Advanced: lower- and uppercase letters from all three rows, dot and comma 
- Use a fixed grammatical structure to generate sentences, but insert random words in runtime to construct a meaningful sentence.

### Optional:
- Offer multiple layouts in different languages
- Display the keyboard layout in the command line and mark the next key. 

## Sprint 3 
### Goal
Optimize performance of the software and tidy up the code to make it more readable
- Collect statistics about the behavior of the user, e.g., time interval between keystrokes, the frequency of errors for every character or combinations of characters. 
- Collect statistics about the lag of the software.
- Analyze performance and identify inefficient parts of the code. Apply optimization techniques to improve them. 
- Refactor the code to make it more readable and maintainable. Separate the functionality according to the model-view-controller model to make it possible to replace or extend individual modules, e.g., replace the command line interface with a web UI, without readjusting the whole code. 
### Definiton of "done":
- The user can see detailed statistics in the `show progress` menu: most problematic characters, errors per row, errors per finger, slowest letter combinations. 
- A file `performance.md` presents your observations from the performance analysis and describes optimization techniques you applied.
- The code follows the model-view-controller pattern. A file `structure.md` describes the logical structure of the program and gives instructions on how to add further functionality. 
### Optional:
- Spinning-up a web-server to move the input/output environment to the web over http and tcp websockets
- Add a web user interface
- Replace .txt-based storage with a sequalized (or not-sequalized) data base












######################################################################################################################################################################
## Getting started

To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.lrz.de/advprog2022/65/typing-trainer.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://gitlab.lrz.de/advprog2022/65/typing-trainer/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Automatically merge when pipeline succeeds](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing(SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thank you to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
