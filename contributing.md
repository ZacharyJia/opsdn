<!-- omit in toc -->
# Contributing to OPSDN

First off, thanks for taking the time to contribute! ❤️

All types of contributions are encouraged and valued. See the [Table of Contents](#table-of-contents) for different ways to help and details about how this project handles them. Please make sure to read the relevant section before making your contribution. It will make it a lot easier for us maintainers and smooth out the experience for all involved. The community looks forward to your contributions. 🎉

> And if you like the project, but just don't have time to contribute, that's fine. There are other easy ways to support the project and show your appreciation, which we would also be very happy about:
> - Star the project
> - Refer this project in your project's readme
> - Mention the project at local meetups and tell your friends/colleagues
> - Cite the paper related to this project in your publications

<!-- omit in toc -->
## Table of Contents

- [I Have a Question](#i-have-a-question)
- [I Want To Contribute](#i-want-to-contribute)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Your First Code Contribution](#your-first-code-contribution)
- [Improving The Documentation](#improving-the-documentation)


## I Have a Question

> If you want to ask a question, we assume that you have read the available [Documentation](https://github.com/ZacharyJia/opsdn/blob/master/README.md).

Before you ask a question, it is best to search for existing [Issues](https://github.com/ZacharyJia/opsdn/issues) that might help you. In case you have found a suitable issue and still need clarification, you can write your question in this issue. It is also advisable to search the internet for answers first.

If you then still feel the need to ask a question and need clarification, we recommend the following:

- Open an [Issue](https://github.com/ZacharyJia/opsdn/issues/new).
- Provide as much context as you can about what you're running into.
- Provide project and platform versions (OS, OPNET Modeler, Python, etc), depending on what seems relevant.

We will then take care of the issue as soon as possible.

<!--
You might want to create a separate issue tag for questions and include it in this description. People should then tag their issues accordingly.

Depending on how large the project is, you may want to outsource the questioning, e.g. to Stack Overflow or Gitter. You may add additional contact and information possibilities:
- IRC
- Slack
- Gitter
- Stack Overflow tag
- Blog
- FAQ
- Roadmap
- E-Mail List
- Forum
-->

## I Want To Contribute

> ### Legal Notice <!-- omit in toc -->
> When contributing to this project, you must agree that you have authored 100% of the content, that you have the necessary rights to the content and that the content you contribute may be provided under the project license.

### Reporting Bugs

<!-- omit in toc -->
#### Before Submitting a Bug Report

A good bug report shouldn't leave others needing to chase you up for more information. Therefore, we ask you to investigate carefully, collect information and describe the issue in detail in your report. Please complete the following steps in advance to help us fix any potential bug as fast as possible.

- Make sure that you are using the latest version.
- Determine if your bug is really a bug and not an error on your side e.g. using incompatible environment components/versions (Make sure that you have read the [documentation](https://github.com/ZacharyJia/opsdn/blob/master/README.md). If you are looking for support, you might want to check [this section](#i-have-a-question)).
- To see if other users have experienced (and potentially already solved) the same issue you are having, check if there is not already a bug report existing for your bug or error in the [bug tracker](https://github.com/ZacharyJia/opsdn/issues?q=label%3Abug).
- Also make sure to search the internet (including Stack Overflow) to see if users outside of the GitHub community have discussed the issue.
- Collect information about the bug:
- Stack trace (Traceback)
- OS, Platform and Version (Windows, Modeler, Python, etc.)
- Possibly your input and the output
- Can you reliably reproduce the issue? And can you also reproduce it with older versions?

<!-- omit in toc -->
#### How Do I Submit a Good Bug Report?


We use GitHub issues to track bugs and errors. If you run into an issue with the project:

- Open an [Issue](https://github.com/ZacharyJia/opsdn/issues/new). (Since we can't be sure at this point whether it is a bug or not, we ask you not to talk about a bug yet and not to label the issue.)
- Explain the behavior you would expect and the actual behavior.
- Please provide as much context as possible and describe the *reproduction steps* that someone else can follow to recreate the issue on their own. This usually includes your code. For good bug reports you should isolate the problem and create a reduced test case.
- Provide the information you collected in the previous section.

Once it's filed:

- I will label the issue accordingly.
- I will try to reproduce the issue with your provided steps. If there are no reproduction steps or no obvious way to reproduce the issue, I will ask you for those steps and mark the issue as `needs-repro`. Bugs with the `needs-repro` tag will not be addressed until they are reproduced.
- If I am able to reproduce the issue, it will be marked `needs-fix`, as well as possibly other tags (such as `critical`), and the issue will be left to be [implemented by someone](#your-first-code-contribution).

<!-- You might want to create an issue template for bugs and errors that can be used as a guide and that defines the structure of the information to be included. If you do so, reference it here in the description. -->


### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for OPSDN, **including completely new features and minor improvements to existing functionality**. Following these guidelines will help maintainers and the community to understand your suggestion and find related suggestions.

<!-- omit in toc -->
#### Before Submitting an Enhancement

- Make sure that you are using the latest version.
- Read the [documentation](https://github.com/ZacharyJia/opsdn/blob/master/README.md) carefully and find out if the functionality is already covered, maybe by an individual configuration.
- Perform a [search](https://github.com/ZacharyJia/opsdn/issues) to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.
- Find out whether your idea fits with the scope and aims of the project. It's up to you to make a strong case to convince the project's developers of the merits of this feature. Keep in mind that we want features that will be useful to the majority of our users and not just a small subset. If you're just targeting a minority of users, consider writing an add-on/plugin library.

<!-- omit in toc -->
#### How Do I Submit a Good Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://github.com/ZacharyJia/opsdn/issues).

- Use a **clear and descriptive title** for the issue to identify the suggestion.
- Provide a **step-by-step description of the suggested enhancement** in as many details as possible.
- **Describe the current behavior** and **explain which behavior you expected to see instead** and why. At this point you can also tell which alternatives do not work for you.
- You may want to **include screenshots and animated GIFs** which help you demonstrate the steps or point out the part which the suggestion is related to. You can use [this tool](https://www.cockos.com/licecap/) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux. <!-- this should only be included if the project has a GUI -->
- **Explain why this enhancement would be useful** to most OPSDN users. You may also want to point out the other projects that solved it better and which could serve as inspiration.

<!-- You might want to create an issue template for enhancement suggestions that can be used as a guide and that defines the structure of the information to be included. If you do so, reference it here in the description. -->

### Your First Code Contribution
<!-- TODO
include Setup of env, IDE and typical getting started instructions?

-->

Here are the steps to help you get started with your first code contribution:

1. Fork the OPSDN repository on GitHub.
1. Clone your forked repository to your local machine.
1. Create a new branch to work on. This can be done using the `git checkout -b` command, like so: `git checkout -b my-new-feature`
1. Implement your new code, making sure to follow the existing code style and conventions. 
1. Test your changes locally to make sure they work as expected.
1. Commit your changes using clear, concise commit messages. For example: "Add new feature X", "Update documentation for Y", "Fix issue with Z". If you made modifications to the models(node models, process models, etc), don't forget to include them in your commit. And please make sure to describe all your modifications to them, because they are in binary format and hard to diff.
1. Push your changes to your forked repository on GitHub.
1. Create a pull request from your forked repository to the main OPSDN repository.
1. Wait for the OPSDN team to review your code and provide feedback.

If you're not sure what to work on, take a look at the open issues on our GitHub repository. We also have a list of feature requests and bug reports that you can work on.

### Improving The Documentation
<!-- TODO
Updating, improving and correcting the documentation

-->
One of the easiest ways to contribute to OPSDN is by improving the project's documentation. Clear and comprehensive documentation helps new users get started with the project and makes it easier for current users to use and understand the project. Here are some guidelines to help you improve the documentation:

1. Read through the current documentation to identify any areas that are unclear, incomplete, or could be improved.
2. Identify the documentation that needs to be fixed or added. This could include README files, installation instructions, API references, or tutorial guides.
3. Write clear, concise, and accurate documentation that follows the project's style and conventions.
4. Submit your documentation changes as a pull request on GitHub.
5. Wait for the OPSDN team to review your changes and provide feedback.

If you're not sure where to start, here are some documentation improvements that would be greatly appreciated:

1. Improving the installation instructions for OPSDN
2. Documenting the available APIs and how to use them
3. Creating more tutorials and guides for using OPSDN in different use cases

Thanks for helping to improve OPSDN's documentation!

<!-- omit in toc -->
## Attribution
This guide is based on the **contributing-gen**. [Make your own](https://github.com/bttger/contributing-gen)!