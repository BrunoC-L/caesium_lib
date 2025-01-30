# caesium_lib
C++ Type Safe Extensible &amp; Accessible Components

Example Usage, basic test file for now! [import_lib/main.cpp](https://github.com/BrunoC-L/caesium_lib/blob/main/import_lib/main.cpp)

## Principles

### Correct Defaults

- Deleted Empty Constructors
- Deleted Copy Constructors
- Deleted Copy Assignments
- Default Move Constructors
- Default Move Assignments
- Deleted std::move(rvalue) & std::move(const lvalue)

### Simplicity

- Do not mess with basic types
- Wrap STL Types

### Accessibility & Extensibility

- Offer Free Functions Instead of Member Functions
- Offer All Functions For a Type In Its' Namespace
