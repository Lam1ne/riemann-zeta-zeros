# Configuration Sample Extension

This sample shows

- How to define a `window`, `resource` and `language-overridable` scoped configurations.
- How to read and update a `window` scoped configuration
- How to read a `resource` scoped configuration of a resource
- How to update a value for `resource` scoped configuration of a resource
- How to read a `language-overridable` scoped configuration
- How to override a `language-overridable` scoped configuration under a language
- How to listen to configuration changes
- How to test it

See [extension.ts](./src/extension.ts)

# Testing

## Empty Workspace

Explains how to test this extension in an Empty workspace

### Testing Window configuration

- Open User Settings and set `"conf.view.showOnWindowOpen": "scm"`
- Refresh the Window. SCM view will be shown always, even if you refresh from a view other than SCM.
- Run the command `Configure view to show on window open` and Select the value (View to show when opening a window)
- Value should be updated in `User Settings`

### Testing Resource configuration

- Open User Settings and set `"conf.resource.insertEmptyLastLine": {"${absolute_path_to_file}": true}`
- Open the above configured file in the empty window. A message about adding empty line from the extension is shown.
- Open a different file. No message is shown.
- Run the command `Configure empty last line for current file`
- Value in User settings is updated. Message is shown now
- Run the command `Configure empty last line for files` and provide absolute path of another file
- Value should be updated in User Settings

### Testing Language Specific configuration

- Set `"conf.language.showSize": true` in user settings
- Open a file and you should see the size of the file in the status
- Unset `conf.language.showSize`
- Run the command `Configuration Sample: Configure show size for language`
- Enter the language for which you want to configure this feature and press Enter.
- Open a file with above configured language and size of the file is shown in status
- Open a file with a different language and no status is shown.


## Folder Workspace

Explains how to test this extension in a Folder workspace

### Testing Window configuration

- Open User or Workspace Settings and set `"conf.view.showOnWindowOpen": "scm"`
- Refresh the Window. SCM view will be shown always, even if you refresh from a view other than SCM.
- Run the command `Configure view to show on window open`. Select the value (View to show when opening a window)
- Pick the target `User Settings` or `Workspace Settings` into which the value should be updated
- Value should be updated in selected target

### Testing Resource configuration

- Open User Settings and set `"conf.resource.insertEmptyLastLine": {"${absolute_path_to_file}": true}`
- Open the above configured file in the empty window. A message about adding empty line from the extension is shown.
- Open a different file from the opened folder. No message is shown.
- Run the command `Configure empty last line for current file`
- Value in Workspace settings is updated. Message is shown now.
- Run the command `Configure empty last line for files` and provide absolute path of another file.
- Pick the target `User Settings` or `Workspace Settings` into which the value should be updated
- Value should be updated in selected target

### Testing Language Specific configuration

- Set `"conf.language.showSize": true` in any settings (user, workspace)
- Open a file and you should see the size of the file in the status
- Unset `conf.language.showSize`
- Run the command `Configuration Sample: Configure show size for language`
- Enter the language for which you want to configure this feature and press Enter.
- Open a file with above configured language and size of the file is shown in status
- Open a file with a different language and no status is shown.


### Multiroot Workspace

Explains how to test this extension in a Multiroot workspace

### Testing Window configuration

- Open User or Workspace Settings and set `"conf.view.showOnWindowOpen": "scm"`
- Refresh the Window. SCM view will be shown always, even if you refresh from a view other than SCM.
- *NOTE*: This setting cannot be applied under Folder settings, doing so will show a warning and value is not respected.
- Run the command `Configure view to show on window open`. Select the value (View to show when opening a window)
- Pick the target `User Settings` or `Workspace Settings` into which the value should be updated
- Value should be updated in selected target

### Testing Resource configuration

- Open User Settings and set `"conf.resource.insertEmptyLastLine": {"${absolute_path_to_file}": true}`
- Open the above configured file in the empty window. A message about adding empty line from the extension is shown.
- Open a different file from one of the root folders. No message is shown.
- Run the command `Configure empty last line for current file`
- Value in Folder Settings of the root folder of the current file is updated. Message is shown now.
- Run the command `Configure empty last line for files` and provide absolute path of another file.
- Pick the target `User Settings` or `Workspace Settings` or `Workspace Folder Settings` into which the value should be updated
- Selecting User or Workspace Settings should update the value in respective targets.
- Selecting Workspace Folder Settings will show a Workspace Folder Picker
- Picking a workspace folder should update the value in the respective folder settings file.

### Testing Language Specific configuration

- Set `"conf.language.showSize": true` in any settings (user, workspace or workspace folder)
- Open a file and you should see the size of the file in the status
- Unset `conf.language.showSize`
- Run the command `Configuration Sample: Configure show size for language`
- Enter the language for which you want to configure this feature and press Enter.
- Open a file with above configured language and size of the file is shown in status
- Open a file with a different language and no status is shown.

# Computation and Visualization of Non-Trivial Zeros of the Riemann Zeta Function

This project allows you to:
- Numerically compute non-trivial zeros of the Riemann zeta function on the critical line using an optimized C++ program (Riemann-Siegel formula).
- Visualize the zeta function in the complex plane and overlay the computed zeros using a Python script.

## Usage

### 1. Compute Zeros (C++)

Compile and run:
```sh
g++ -O3 -fopenmp riemann_zero.cpp -o riemann_zero.exe
./riemann_zero.exe
```
The found zeros are saved in `zeros.txt` and Z(t) values in `zeta_plot.csv`.

### 2. Visualization (Python)

Install dependencies:
```sh
pip install numpy matplotlib mpmath pandas
```

Run the visualization script:
```sh
python zeta_2d_with_zeros.py
```
This script displays a color map of |ζ(s)| in the complex plane and marks the zeros computed in C++ on the critical line.

## Main Files

- `riemann_zero.cpp`: Computes zeros and exports CSV.
- `zeta_2d_with_zeros.py`: Advanced visualization in Python.
- `.gitignore`: Ignores generated and temporary files.

## Notes

- Computation off the critical line is done in Python (mpmath library).
- The C++ code uses only standard libraries for portability and mathematical clarity.
