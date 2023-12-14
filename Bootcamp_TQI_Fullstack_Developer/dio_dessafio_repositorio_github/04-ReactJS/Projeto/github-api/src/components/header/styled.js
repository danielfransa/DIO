import styled from "styled-components";

export const Wrapper = styled.div `
    display: flex;
    width: 100%;
    justify-content:space-between;
    padding: 6px;

    input {
        border: 2px solid #ccc;
        border-radius: 8px;
        width: 100%;
        height: 50px;
        margin-right: 6px;
        padding: 4px;
        font-weight: 500;
    }

    button {
        background-color: #ccb;
        padding: 8px;
        margin: 8px;
        border: 1px solid #000;
        border-radius: 8px;
        
        &:hover {
            background-color: #ccc;
            box-shadow: 3px 2px 10px rgba(0, 0, 0, 0.2);
    }    

    span {
        font-weight: bold;
        font-size: 16px;
    }
    
    }
`