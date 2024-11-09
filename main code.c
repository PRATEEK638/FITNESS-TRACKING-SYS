#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User profile structure
struct UserProfile {
    int id;
    char name[50];
    int age;
    float height; // in cm
    float weight; // in kg
    float bmi;    // BMI calculated
};

// Workout structure
struct Workout {
    int id;
    char exercise[50];
    float duration; // in minutes
    char intensity[10]; // Low/Medium/High
    float calories; // calories burned
};

// Diet structure
struct Diet {
    int id;
    char meal[50];
    float quantity; // quantity in grams
    float calories; // calories for the meal
    char type[20];  // Meal type (Breakfast/Lunch/Dinner/Snack)
};

// Function to calculate BMI
float calculate_bmi(float weight, float height) {
    return weight / ((height / 100) * (height / 100)); // BMI = weight(kg) / height(m)^2
}

// Function to save profiles to CSV file
void save_profile_to_csv(struct UserProfile user) {
    FILE *file = fopen("profiles.csv", "a");
    if (file == NULL) {
        printf("Error opening profiles.csv file!\n");
        return;
    }
    fprintf(file, "%d,%s,%d,%.2f,%.2f,%.2f\n", user.id, user.name, user.age, user.height, user.weight, user.bmi);
    fclose(file);
}

// Function to save workout to CSV file
void save_workout_to_csv(struct Workout workout) {
    FILE *file = fopen("workouts.csv", "a");
    if (file == NULL) {
        printf("Error opening workouts.csv file!\n");
        return;
    }
    fprintf(file, "%d,%s,%.2f,%s,%.2f\n", workout.id, workout.exercise, workout.duration, workout.intensity, workout.calories);
    fclose(file);
}

// Function to save diet to CSV file
void save_diet_to_csv(struct Diet diet) {
    FILE *file = fopen("diets.csv", "a");
    if (file == NULL) {
        printf("Error opening diets.csv file!\n");
        return;
    }
    fprintf(file, "%d,%s,%.2f,%.2f,%s\n", diet.id, diet.meal, diet.quantity, diet.calories, diet.type);
    fclose(file);
}

// Function to create a user profile
void create_profile(int *profile_count) {
    struct UserProfile user;
    user.id = (*profile_count) + 1;

    printf("Enter your name: ");
    fgets(user.name, 50, stdin);
    user.name[strcspn(user.name, "\n")] = 0; // Remove newline character

    printf("Enter your age: ");
    scanf("%d", &user.age);

    printf("Enter your height (in cm): ");
    scanf("%f", &user.height);

    printf("Enter your weight (in kg): ");
    scanf("%f", &user.weight);

    user.bmi = calculate_bmi(user.weight, user.height);
    (*profile_count)++;

    save_profile_to_csv(user);
    printf("Profile created with ID: %d!\n", user.id);
    getchar(); // To consume the newline after scanf
}

// Function to log a workout
void log_workout(int profile_id) {
    struct Workout workout;
    workout.id = profile_id;

    printf("Enter exercise name (e.g., 'Push Ups', 'Running', 'Cycling', 'Squats'): ");
    fgets(workout.exercise, 50, stdin);
    workout.exercise[strcspn(workout.exercise, "\n")] = 0;

    printf("Enter duration (minutes): ");
    scanf("%f", &workout.duration);

    printf("Enter intensity (Low/Medium/High): ");
    scanf("%s", workout.intensity);

    // Calorie calculation based on intensity and exercise type
    if (strcmp(workout.exercise, "Push Ups") == 0) {
        workout.calories = workout.duration * 7;
    } else if (strcmp(workout.exercise, "Running") == 0) {
        workout.calories = workout.duration * 10;
    } else {
        workout.calories = workout.duration * 5; // Default for other exercises
    }

    save_workout_to_csv(workout);
    printf("Workout logged for profile ID: %d!\n", profile_id);
    getchar(); // To consume newline
}

// Function to log a diet
void log_diet(int profile_id) {
    struct Diet diet;
    diet.id = profile_id;

    printf("Enter meal description (e.g., 'Grilled Chicken', 'Vegetable Salad', 'Oatmeal', 'Fruit Smoothie'): ");
    fgets(diet.meal, 50, stdin);
    diet.meal[strcspn(diet.meal, "\n")] = 0;

    printf("Enter quantity (in grams): ");
    scanf("%f", &diet.quantity);

    // Example calorie calculation based on meal type and quantity
    if (strcmp(diet.meal, "Grilled Chicken") == 0) {
        diet.calories = (diet.quantity / 100) * 165;
    } else {
        diet.calories = (diet.quantity / 100) * 50; // Default calorie for other meals
    }

    printf("Enter meal type (Breakfast/Lunch/Dinner/Snack): ");
    scanf("%s", diet.type);

    save_diet_to_csv(diet);
    printf("Diet logged for profile ID: %d!\n", profile_id);
    getchar(); // To consume newline
}

// Function to display a profile
void display_profile(int profile_id) {
    FILE *file = fopen("profiles.csv", "r");
    if (file == NULL) {
        printf("Error opening profiles.csv file!\n");
        return;
    }

    struct UserProfile user;
    while (fscanf(file, "%d,%[^,],%d,%f,%f,%f\n", &user.id, user.name, &user.age, &user.height, &user.weight, &user.bmi) != EOF) {
        if (user.id == profile_id) {
            printf("\nProfile ID: %d\n", user.id);
            printf("Name: %s, Age: %d, Height: %.2f cm, Weight: %.2f kg\n", user.name, user.age, user.height, user.weight);
            printf("BMI: %.2f\n", user.bmi);
            break;
        }
    }

    fclose(file);
}

// Function to display workout for a profile
void display_workout(int profile_id) {
    FILE *file = fopen("workouts.csv", "r");
    if (file == NULL) {
        printf("Error opening workouts.csv file!\n");
        return;
    }

    struct Workout workout;
    while (fscanf(file, "%d,%[^,],%f,%[^,],%f\n", &workout.id, workout.exercise, &workout.duration, workout.intensity, &workout.calories) != EOF) {
        if (workout.id == profile_id) {
            printf("\nWorkout Log for Profile ID %d:\n", profile_id);
            printf("Exercise: %s, Duration: %.2f mins, Intensity: %s, Calories burned: %.2f\n",
                   workout.exercise, workout.duration, workout.intensity, workout.calories);
            break;
        }
    }

    fclose(file);
}

// Function to display diet for a profile
void display_diet(int profile_id) {
    FILE *file = fopen("diets.csv", "r");
    if (file == NULL) {
        printf("Error opening diets.csv file!\n");
        return;
    }

    struct Diet diet;
    while (fscanf(file, "%d,%[^,],%f,%f,%s\n", &diet.id, diet.meal, &diet.quantity, &diet.calories, diet.type) != EOF) {
        if (diet.id == profile_id) {
            printf("\nDiet Log for Profile ID %d:\n", profile_id);
            printf("Meal: %s, Quantity: %.2f grams, Calories: %.2f, Type: %s\n",
                   diet.meal, diet.quantity, diet.calories, diet.type);
            break;
        }
    }

    fclose(file);
}

// Main menu
int main() {
    int choice, profile_id;
    int profile_count = 0;

    while (1) {
        printf("\n===== Fitness Tracker Menu =====\n");
        printf("1. Create Profile\n");
        printf("2. Log Workout\n");
        printf("3. Log Diet\n");
        printf("4. Display Profile Information\n");
        printf("5. Display Workout Log\n");
        printf("6. Display Diet Log\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline left in buffer

        switch (choice) {
            case 1:
                create_profile(&profile_count);
                break;
            case 2:
                printf("Enter profile ID: ");
                scanf("%d", &profile_id);
                getchar(); // To consume newline left in buffer
                log_workout(profile_id);
                break;
            case 3:
                printf("Enter profile ID: ");
                scanf("%d", &profile_id);
                getchar(); // To consume newline left in buffer
                log_diet(profile_id);
                break;
            case 4:
                printf("Enter profile ID: ");
                scanf("%d", &profile_id);
                display_profile(profile_id);
                break;
            case 5:
                printf("Enter profile ID: ");
                scanf("%d", &profile_id);
                display_workout(profile_id);
                break;
            case 6:
                printf("Enter profile ID: ");
                scanf("%d", &profile_id);
                display_diet(profile_id);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


