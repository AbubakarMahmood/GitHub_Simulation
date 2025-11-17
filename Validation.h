#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>
#include <cctype>

// Validation utility class for input validation
class Validation {
public:
    // Username validation rules:
    // - Length: 3-20 characters
    // - Allowed: alphanumeric, underscore, hyphen
    // - Must start with a letter or number
    static bool isValidUsername(const std::string& username, std::string& errorMessage) {
        if (username.empty()) {
            errorMessage = "Username cannot be empty";
            return false;
        }

        if (username.length() < 3) {
            errorMessage = "Username must be at least 3 characters long";
            return false;
        }

        if (username.length() > 20) {
            errorMessage = "Username cannot exceed 20 characters";
            return false;
        }

        // Check first character is alphanumeric
        if (!std::isalnum(username[0])) {
            errorMessage = "Username must start with a letter or number";
            return false;
        }

        // Check for valid characters (alphanumeric, underscore, hyphen)
        for (char ch : username) {
            if (!std::isalnum(ch) && ch != '_' && ch != '-') {
                errorMessage = "Username can only contain letters, numbers, underscores, and hyphens";
                return false;
            }
        }

        errorMessage = "";
        return true;
    }

    // Password validation rules:
    // - Length: 6-50 characters
    // - Must contain at least one letter and one number
    static bool isValidPassword(const std::string& password, std::string& errorMessage) {
        if (password.empty()) {
            errorMessage = "Password cannot be empty";
            return false;
        }

        if (password.length() < 6) {
            errorMessage = "Password must be at least 6 characters long";
            return false;
        }

        if (password.length() > 50) {
            errorMessage = "Password cannot exceed 50 characters";
            return false;
        }

        bool hasLetter = false;
        bool hasNumber = false;

        for (char ch : password) {
            if (std::isalpha(ch)) hasLetter = true;
            if (std::isdigit(ch)) hasNumber = true;
        }

        if (!hasLetter || !hasNumber) {
            errorMessage = "Password must contain at least one letter and one number";
            return false;
        }

        errorMessage = "";
        return true;
    }

    // Repository name validation rules:
    // - Length: 1-100 characters
    // - Allowed: alphanumeric, underscore, hyphen, dot
    // - Cannot start or end with special characters
    // - No consecutive special characters
    static bool isValidRepositoryName(const std::string& repoName, std::string& errorMessage) {
        if (repoName.empty()) {
            errorMessage = "Repository name cannot be empty";
            return false;
        }

        if (repoName.length() > 100) {
            errorMessage = "Repository name cannot exceed 100 characters";
            return false;
        }

        // Check first and last character are alphanumeric
        if (!std::isalnum(repoName[0])) {
            errorMessage = "Repository name must start with a letter or number";
            return false;
        }

        if (!std::isalnum(repoName[repoName.length() - 1])) {
            errorMessage = "Repository name must end with a letter or number";
            return false;
        }

        // Check for valid characters and no consecutive special characters
        char prevChar = '\0';
        for (char ch : repoName) {
            if (!std::isalnum(ch) && ch != '_' && ch != '-' && ch != '.') {
                errorMessage = "Repository name can only contain letters, numbers, underscores, hyphens, and dots";
                return false;
            }

            // Check for consecutive special characters
            if (!std::isalnum(ch) && !std::isalnum(prevChar) && prevChar != '\0') {
                errorMessage = "Repository name cannot have consecutive special characters";
                return false;
            }

            prevChar = ch;
        }

        // Reserved names
        if (repoName == "." || repoName == ".." || repoName == "CON" ||
            repoName == "PRN" || repoName == "AUX" || repoName == "NUL") {
            errorMessage = "Repository name is reserved and cannot be used";
            return false;
        }

        errorMessage = "";
        return true;
    }

    // File name validation rules:
    // - Length: 1-255 characters
    // - Allowed: alphanumeric, underscore, hyphen, dot, space
    // - Cannot start or end with space
    // - Must have valid extension
    // - No path separators
    static bool isValidFileName(const std::string& fileName, std::string& errorMessage) {
        if (fileName.empty()) {
            errorMessage = "File name cannot be empty";
            return false;
        }

        if (fileName.length() > 255) {
            errorMessage = "File name cannot exceed 255 characters";
            return false;
        }

        // Check for leading or trailing spaces
        if (fileName[0] == ' ' || fileName[fileName.length() - 1] == ' ') {
            errorMessage = "File name cannot start or end with a space";
            return false;
        }

        // Check for invalid characters (especially path separators)
        for (char ch : fileName) {
            if (ch == '/' || ch == '\\' || ch == ':' || ch == '*' ||
                ch == '?' || ch == '"' || ch == '<' || ch == '>' || ch == '|') {
                errorMessage = "File name contains invalid characters";
                return false;
            }
        }

        // Reserved names
        if (fileName == "." || fileName == ".." || fileName == "CON" ||
            fileName == "PRN" || fileName == "AUX" || fileName == "NUL" ||
            fileName == "COM1" || fileName == "LPT1") {
            errorMessage = "File name is reserved and cannot be used";
            return false;
        }

        // Check for file extension
        size_t dotPos = fileName.find_last_of('.');
        if (dotPos == std::string::npos || dotPos == fileName.length() - 1) {
            errorMessage = "File name must have a valid extension (e.g., .txt, .cpp, .md)";
            return false;
        }

        errorMessage = "";
        return true;
    }

    // Commit message validation rules:
    // - Length: 1-500 characters
    // - Cannot be only whitespace
    static bool isValidCommitMessage(const std::string& message, std::string& errorMessage) {
        if (message.empty()) {
            errorMessage = "Commit message cannot be empty";
            return false;
        }

        // Check if only whitespace
        bool hasNonWhitespace = false;
        for (char ch : message) {
            if (!std::isspace(ch)) {
                hasNonWhitespace = true;
                break;
            }
        }

        if (!hasNonWhitespace) {
            errorMessage = "Commit message cannot be only whitespace";
            return false;
        }

        if (message.length() > 500) {
            errorMessage = "Commit message cannot exceed 500 characters";
            return false;
        }

        errorMessage = "";
        return true;
    }
};

#endif // VALIDATION_H
