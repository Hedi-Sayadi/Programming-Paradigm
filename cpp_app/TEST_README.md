# MediCheck Test Suite Documentation

## Overview
This document describes the comprehensive test suite for the MediCheck C++ application. The test suite validates all core functionality including patient management, symptom tracking, disease diagnosis, and data persistence.

## Test Files
- `test_medicheck.cpp` - Main test suite implementation
- `build_test.bat` - Windows build script for tests
- `bin/test_medicheck.exe` - Compiled test executable

## Quick Start

### Building the Tests
```bash
# Windows
.\build_test.bat
```

### Running the Tests
```bash
# Windows
.\bin\test_medicheck.exe
```

## Test Categories

### 1. Patient Management Tests
Tests the core patient CRUD (Create, Read, Update, Delete) operations:

| Test | Description | Expected Result |
|------|-------------|-----------------|
| Add Patients | Creates 3 test patients | 3 patients in system |
| Find Patient by ID | Searches for patient ID 1 | Returns John Doe |
| Patient Data Integrity | Verifies name, age, gender | Data matches input |
| Delete Patient | Removes patient ID 2 | Patient count reduces |
| Handle Non-existent | Searches for ID 999 | Returns null pointer |

### 2. Symptom Management Tests
Tests symptom addition, removal, and validation:

| Test | Description | Expected Result |
|------|-------------|-----------------|
| Add Symptoms | Adds fever, cough, headache | 3 symptoms added |
| Duplicate Prevention | Adds fever again | No duplicate created |
| Clear Symptoms | Removes all symptoms | Empty symptom list |
| Available Symptoms | Validates symptom catalog | 18 symptoms available |
| Symptom Order | Checks first two symptoms | fever, cough |

### 3. Diagnosis Engine Tests
Tests the disease prediction algorithm:

| Test | Description | Input Symptoms | Expected Disease |
|------|-------------|----------------|------------------|
| Common Cold | Basic cold symptoms | runny nose, sore throat | Common Cold |
| Flu Detection | Influenza symptoms | fever, cough | Flu |
| COVID-19 Detection | Pandemic symptoms | fever, cough, loss of taste | COVID-19 |
| Pneumonia Detection | Lung infection | fever, cough, shortness of breath | Pneumonia |
| Empty Input | No symptoms | none | No diseases |

### 4. CSV Persistence Tests
Tests data storage and file handling:

| Test | Description | Expected Result |
|------|-------------|-----------------|
| Patient CSV Creation | File exists after patient add | data/patients.csv created |
| Patient CSV Header | Validates file format | "id,name,age,gender" |
| Patient CSV Content | Searches for test data | "John Doe" found |
| Symptoms CSV Creation | File exists after symptom add | data/symptoms.csv created |
| Symptoms CSV Header | Validates file format | "patient_id,symptoms" |
| Symptoms CSV Content | Searches for test symptoms | "1,fever;cough;headache" |

### 5. Data Loading Tests
Tests CSV data restoration:

| Test | Description | Expected Result |
|------|-------------|-----------------|
| Load Patient Count | Restore from CSV | Count > 0 |
| Load Patient Data | Restore John Doe | Name, age, gender match |
| Load Symptoms | Restore patient symptoms | Symptom list not empty |
| Symptom Integrity | Verify specific symptoms | fever/cough/headache present |

## Test Output Format

### Success Indicators
- **PASS**: Test completed successfully
- **FAIL**: Test failed (requires investigation)

### Example Output
```
========================================
     MediCheck Test Suite Starting     
========================================

--- Testing Patient Management ---
 PASS: Add 3 patients
 PASS: Find patient by ID 1
 PASS: Patient 1 has correct name
 PASS: All tests completed successfully

========================================
           Test Results Summary         
========================================
Tests Passed: 33
Tests Failed: 0
Total Tests:  33
Success Rate: 100%

All tests passed! The application is working correctly.
```

## Test Data Management

### Automatic Cleanup
The test suite automatically:
- Removes existing CSV files before testing
- Creates fresh test data
- Cleans up after completion

### Test Data Files
During testing, these files are created in `data/`:
- `patients.csv` - Test patient records
- `symptoms.csv` - Test symptom associations

### CSV Format Validation
Tests verify the following CSV formats:

**patients.csv:**
```csv
id,name,age,gender
1,John Doe,30,M
2,Jane Smith,25,F
```

**symptoms.csv:**
```csv
patient_id,symptoms
1,fever;cough;headache
2,nausea;vomiting
```

## Troubleshooting

### Build Failures
```bash
# Check compiler availability
g++ --version

# Verify file paths
dir *.cpp *.h

# Clean build
del bin\test_medicheck.exe
.\build_test.bat
```

### Test Failures
1. **CSV Permission Issues**
   - Ensure data/ directory is writable
   - Close any open CSV files

2. **Missing Dependencies**
   - Verify all .cpp and .h files present
   - Check includes in source files

3. **Memory Issues**
   - Restart terminal/IDE
   - Clean rebuild application

### Common Issues

| Error | Cause | Solution |
|-------|--------|----------|
| File not found | Missing source files | Verify all files present |
| Permission denied | CSV files locked | Close Excel/editors |
| Compiler error | Code syntax issues | Fix compilation errors |
| Test timeout | Infinite loops | Debug failing test |

## Extending the Test Suite

### Adding New Tests
1. Add test function to `MediCheckTester` class
2. Call from `runAllTests()`
3. Use `assertTrue()` for validation
4. Update this documentation

### Test Function Template
```cpp
void testNewFeature() {
    cout << "--- Testing New Feature ---\n";
    
    // Setup
    // ... test setup code ...
    
    // Execute & Verify
    assertTrue(condition, "Test description");
    
    cout << "\n";
}
```

### Best Practices
- One assertion per test case
- Clear, descriptive test names
- Clean up test data
- Test both success and failure cases
- Validate error handling

## Integration with CI/CD

### Command Line Usage
```bash
# Silent run (return codes only)
.\bin\test_medicheck.exe > test_results.txt
echo %ERRORLEVEL%

# Parse results
findstr "Success Rate" test_results.txt
```

### Return Codes
- `0` - All tests passed
- `1` - Some tests failed

## Performance Considerations

### Test Execution Time
- Typical runtime: 1-3 seconds
- File I/O operations are the slowest
- In-memory tests execute quickly

### Memory Usage
- Minimal memory footprint
- Test data is small
- No memory leaks in test framework

## Maintenance

### Regular Updates
- Update tests when adding features
- Verify test data remains valid
- Review test coverage periodically

### Version Compatibility
- Tests designed for current MediCheck version
- Update test data format when CSV changes
- Maintain backward compatibility where possible

---

## Support

For issues with the test suite:
1. Check this documentation
2. Verify build environment
3. Review error messages carefully
4. Test individual components

**Remember**: A well-tested application is a reliable application!
