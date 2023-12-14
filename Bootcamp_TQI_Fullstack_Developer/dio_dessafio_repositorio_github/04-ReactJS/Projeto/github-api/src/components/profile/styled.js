import styled from 'styled-components';

export const Wrapper = styled.div`
display: flex;
align-items: flex-start;
`;

export const WrapperInfoUser = styled.div`
display: flex;
flex-direction: column;
align-items: flex-start;
justify-content: space-between;
height: 225px;
margin-left: 10px;

h1 {
    font-size: 38px;
    font-weight: bold;
}

h3 {
    font-size: 24px;
    font-weight: bold;
}

h4 {
    font-size: 20px;
    font-weight: bold;
}
`;

export const WrapperStatusCount = styled.div`
display: flex;
align-items: center;
div {
    margin: 10px;
    text-align: center;
}
`;

export const WrapperUserGeneric = styled.div`
display: flex;
align-items: center;
margin-top: 10px;

h3 {
    margin-right: 10px;
}

a {
    font-size: 22px;
    color: blue;
    font-weight: bold
}
`;

export const WrapperImage = styled.img`
border-radius: 50%;
width: 200px;
margin: 10px;
box-shadow: 0 0 1em #ccc;
`;