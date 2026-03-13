CREATE TABLE Student (
    SID SMALLINT NOT NULL,         -- Unique student ID
    Name VARCHAR(50),              -- Student name, max 50 characters
    Sex NCHAR(10) CHECK (Sex IN ('Male', 'Female')), -- Only Male/Female
    CGPA REAL DEFAULT 0 NOT NULL CHECK (CGPA BETWEEN 0 AND 4), -- Must be between 0 and 4
    DoBirth SMALLDATETIME,         -- Date of birth
    Age SMALLINT,                  -- Age
    CONSTRAINT PK_Student PRIMARY KEY (SID) -- SID is the PRIMARY KEY
);
CREATE TABLE Course (
    CID SMALLINT NOT NULL,          -- Unique course ID
    CTitle VARCHAR(50),             -- Course title
    Credit SMALLINT,                -- Number of credits
    CONSTRAINT PK_Course PRIMARY KEY (CID) -- CID is the PRIMARY KEY
);
CREATE TABLE Takes (
    SID SMALLINT,                  -- Student ID (FK)
    CID SMALLINT,                  -- Course ID (FK)
    Grade CHAR(1),                  -- Grade (A, B, C, D, F)
    CONSTRAINT FK_Student FOREIGN KEY (SID) REFERENCES Student(SID),
    CONSTRAINT FK_Course FOREIGN KEY (CID) REFERENCES Course(CID)
);
