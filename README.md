# Flowchart Designer & Simulator (CMPG102 Programming Techniques)

## 1. Project Title

Flowchart Designer & Simulator
## Team

- Nour Ibrahim
- Youmna Mohamed
- Yasmine Ismail

## 2. Project Overview

A C++ GUI application for designing and simulating basic algorithm flowcharts.

The application allows users to visually construct flowcharts using standard programming statements (Start, End, Declaration, Assignment, Condition, Input, Output), connect them with arrows, validate correctness, and simulate execution. It also supports saving/loading flowcharts and generating equivalent C++ source code (best-effort).

This project follows the CMPG102 Programming Techniques course specification.

## 3. Screenshots / Demo

![Design Mode](images/screenshots/design-mode.png)
> Screenshot showing the design toolbar and a sample flowchart placed on the drawing area.

![Adding Statements](images/screenshots/add-statements.png)
> Screenshot showing a statement being added (e.g., Declare or Assignment) with rendered text.

![Connecting Blocks](images/screenshots/connectors.png)
> Screenshot showing connectors between statements, including a conditional with YES/NO branches.

![Simulation Output](images/screenshots/simulation-output.png)
> Screenshot showing simulation mode with output printed from `Write` statements.

![Validation Error](images/screenshots/validation-error.png)
> Screenshot showing a validation error message (e.g., missing End statement or invalid connectors).

## 4. Features

- GUI-based flowchart design mode
- Supported statements:
  - Start
  - End
  - Declare (double variables)
  - Value assignment
  - Variable assignment
  - Operator assignment (`+`, `-`, `*`, `/`)
  - Conditional statements (`==`, `!=`, `>`, `<`, `>=`, `<=`)
  - Read
  - Write
- Connector creation between statements
  - Conditional statements support YES/NO branching
- Statement and connector selection
- Edit selected statement
- Delete statements or connectors
  - Deleting a statement removes all related connectors
- Copy, Cut, and Paste statements
  - Pasted statements do not include connectors
- Save flowchart to a text file
- Load flowchart from a text file
- Design mode and Simulation mode switching
- Flowchart validation before execution:
  - Exactly one Start and one End
  - No dangling connectors
  - Correct connector count per statement
  - Reachability from Start
  - Variable declaration and usage validation
- Flowchart simulation and execution
- Output display for `Write` statements
- Debug execution support
- C++ code generation (best-effort)

## 5. Technologies Used

- **Language:** C++
- **IDE / Build System:** Microsoft Visual Studio
- **GUI Library:** CMU Graphics Library
- **Assets:** Toolbar and UI images (`.jpg`)

### Key Components

- **ApplicationManager**  
  Central controller managing statements, connectors, clipboard operations, validation, simulation, and action dispatching.

- **GUI/Input & GUI/Output**  
  Handle user interaction, drawing, toolbars, and output/status bars.

- **Statements**  
  Polymorphic hierarchy implementing drawing, saving/loading, validation, simulation, and code generation.

- **Actions**  
  One class per user operation (add, select, edit, delete, save, load, run, etc.).

- **Connector**  
  Represents flow connections between statements, including conditional branches.

## Build & Run

### Requirements
- Windows
- Microsoft Visual Studio (Desktop development with C++)

### Steps
1. Open `PT Project.sln` in Visual Studio.
2. Choose a build configuration (Debug/Release).
3. Build the solution.
4. Run the application from Visual Studio.

## Usage

### Design Mode
1. Select a statement type from the toolbar.
2. Click on the drawing area to place the statement.
3. Use the connector tool to connect statements.
4. Use Select to edit, delete, copy, cut, or paste statements.

### Simulation Mode
1. Switch to simulation mode.
2. Validate the flowchart.
3. Run the flowchart:
   - `Read` prompts for input.
   - `Write` outputs results to the output bar.

## Save File Format

- Text-based format:
  - Number of statements
  - Statement definitions with IDs and geometry
  - Number of connectors
  - Connector definitions (`sourceID destinationID branch`)

Statement tags used internally:
- `STRT`, `ENDS`, `DCLR`, `VLAS`, `VRAS`, `OPAS`, `COND`, `READ`, `WRTE`

Assumption: The save/load format matches the internal implementation and may differ slightly from example formats in the course document.

## Code Generation Notes

- Generates a basic `main()` function in C++
- Supports declarations, assignments, I/O, conditionals, and simple loops
