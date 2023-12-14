import styled from "styled-components";
import { Tabs, TabList, Tab, TabPanel} from "react-tabs"

export const WrapperTabs= styled(Tabs)`
    font-size: 18px;
    width: 100%;
    margin-top: 16px;
`;

export const WrapperTabList= styled(TabList)`
    list-style-type: none;
    padding: 6px;
    display: flex;
    margin: 0px;
`;
WrapperTabList.tabsRole = "TabList"; 

export const WrapperTab= styled(Tab)`
    border-radius: 20px;
    margin: 3px;
    border: 2px solid #ccc;
    padding: 10px;
    user-select: none;
    cursor: pointer;
    z-index: 99999;
    backgroud-color: #fff;
    
    &:focus {
        outline: none;
    }

    &.is-selected {
       box-shadow: 3px 2px 10px rgba(0, 0, 0, 0.2);  
    }
`;
WrapperTab.tabsRole = "Tab";

export const WrapperTabPanel= styled(TabPanel)` 
    display: none;
    border 2px solid #ccc;
    padding: 10px;
    margin-top: -5px;

    &.is-selected {
        display: block;
    }
`;
WrapperTabPanel.tabsRole = "TabPanel";

export const WrapperList = styled.div`
  display: flex;
  justify-content: flex-start;
  flex-wrap: wrap;
`;